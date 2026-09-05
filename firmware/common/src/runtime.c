#include "runtime.h"

#include "controller_state.h"
#include "frame.h"

static void runtime_sample_inputs(
    ES_Runtime *runtime
)
{
    /*
     * Hardware-specific sampling will eventually
     * call the GPIO/ADC driver here.
     *
     * These values are deliberately placeholders.
     */

    uint8_t button_sample;
    uint16_t lx_sample;
    uint16_t ly_sample;
    uint16_t rx_sample;
    uint16_t ry_sample;

    button_sample = 0;

    lx_sample = ES_AXIS_CENTER;
    ly_sample = ES_AXIS_CENTER;

    rx_sample = ES_AXIS_CENTER;
    ry_sample = ES_AXIS_CENTER;

    es_input_update_button(
        &runtime->input,
        0,
        button_sample
    );

    es_input_update_axis(
        &runtime->input.lx,
        lx_sample,
        ES_DEFAULT_DEADZONE
    );

    es_input_update_axis(
        &runtime->input.ly,
        ly_sample,
        ES_DEFAULT_DEADZONE
    );

    es_input_update_axis(
        &runtime->input.rx,
        rx_sample,
        ES_DEFAULT_DEADZONE
    );

    es_input_update_axis(
        &runtime->input.ry,
        ry_sample,
        ES_DEFAULT_DEADZONE
    );

    es_input_finalize(
        &runtime->input
    );
}

static void runtime_generate_frame(
    ES_Runtime *runtime
)
{
    ES_PackedControllerState state;

    uint8_t payload[ES_MAX_PAYLOAD];
    uint8_t payload_length;

    uint8_t frame_buffer[ES_MAX_FRAME];
    uint8_t frame_length;

    es_state_pack(
        &runtime->input,
        &state
    );

    state.frame_counter =
        runtime->sequence;

    payload_length =
        es_state_serialize(
            &state,
            payload
        );

    frame_length =
        es_build_frame(
            frame_buffer,
            sizeof(frame_buffer),
            ES_TYPE_INPUT,
            runtime->sequence,
            payload,
            payload_length
        );

    if (frame_length == 0) {
        runtime->stats.transport_errors++;
        return;
    }

    for (uint8_t i = 0; i < frame_length; i++) {

        if (!es_transport_tx_push(
                &runtime->transport,
                frame_buffer[i])) {

            runtime->stats.transport_errors++;
            return;
        }
    }

    runtime->stats.frames_generated++;

    runtime->sequence++;
}

static void runtime_heartbeat(
    ES_Runtime *runtime
)
{
    /*
     * Communication health indicator.
     *
     * Hardware-specific LED or status output
     * can be connected here later.
     */

    runtime->stats.communication_alive =
        ((runtime->stats.uptime_ms -
          runtime->last_rx_tick)
         <= ES_RX_TIMEOUT_MS);
}

void es_runtime_init(
    ES_Runtime *runtime
)
{
    es_input_init(
        &runtime->input
    );

    es_transport_init(
        &runtime->transport
    );

    es_parser_init(
        &runtime->parser
    );

    runtime->stats.uptime_ms = 0;

    runtime->stats.input_ticks = 0;
    runtime->stats.frame_ticks = 0;
    runtime->stats.heartbeat_ticks = 0;

    runtime->stats.frames_generated = 0;
    runtime->stats.frames_transmitted = 0;
    runtime->stats.frames_received = 0;

    runtime->stats.parser_errors = 0;
    runtime->stats.transport_errors = 0;

    runtime->stats.communication_alive = 0;
    runtime->stats.fault = 0;

    runtime->sequence = 0;

    runtime->next_input_tick = 0;
    runtime->next_frame_tick = 0;
    runtime->next_heartbeat_tick =
        ES_HEARTBEAT_PERIOD_MS;

    runtime->last_rx_tick = 0;
}

void es_runtime_tick(
    ES_Runtime *runtime,
    uint32_t now_ms
)
{
    runtime->stats.uptime_ms = now_ms;

    /*
     * Input sampling
     */
    if (now_ms >= runtime->next_input_tick) {

        runtime_sample_inputs(runtime);

        runtime->stats.input_ticks++;

        runtime->next_input_tick =
            now_ms + ES_INPUT_PERIOD_MS;
    }

    /*
     * Controller frame generation
     */
    if (now_ms >= runtime->next_frame_tick) {

        runtime_generate_frame(runtime);

        runtime->stats.frame_ticks++;

        runtime->next_frame_tick =
            now_ms + ES_FRAME_PERIOD_MS;
    }

    /*
     * Communication heartbeat
     */
    if (now_ms >= runtime->next_heartbeat_tick) {

        runtime_heartbeat(runtime);

        runtime->stats.heartbeat_ticks++;

        runtime->next_heartbeat_tick =
            now_ms + ES_HEARTBEAT_PERIOD_MS;
    }
}

void es_runtime_rx_byte(
    ES_Runtime *runtime,
    uint8_t byte
)
{
    ES_Frame frame;

    if (!es_transport_rx_push(
            &runtime->transport,
            byte)) {

        runtime->stats.transport_errors++;
        return;
    }

    while (es_transport_rx_pop(
        &runtime->transport,
        &byte)) {

        if (es_parser_consume(
                &runtime->parser,
                byte,
                &frame)) {

            runtime->stats.frames_received++;

            runtime->last_rx_tick =
                runtime->stats.uptime_ms;
        }
    }

    runtime->stats.parser_errors =
        runtime->parser.frames_rejected;
}

uint16_t es_runtime_get_sequence(
    const ES_Runtime *runtime
)
{
    return runtime->sequence;
}
