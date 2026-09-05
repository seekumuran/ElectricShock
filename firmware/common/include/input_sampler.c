#include "input_sampler.h"

void es_sampler_init(
    ES_InputSampler *sampler,
    ES_Hardware *hal,
    uint8_t button_count
)
{
    sampler->hal = hal;
    sampler->button_count = button_count;
}

void es_sampler_sample(
    ES_InputSampler *sampler,
    ES_ControllerState *state
)
{
    uint8_t i;

    for (i = 0;
         i < sampler->button_count &&
         i < ES_BUTTON_COUNT;
         i++) {

        uint8_t raw =
            sampler->hal->read_button(i);

        es_input_update_button(
            state,
            i,
            raw
        );
    }

    es_input_update_axis(
        &state->lx,
        sampler->hal->read_axis(ES_AXIS_LX),
        ES_DEFAULT_DEADZONE
    );

    es_input_update_axis(
        &state->ly,
        sampler->hal->read_axis(ES_AXIS_LY),
        ES_DEFAULT_DEADZONE
    );

    es_input_update_axis(
        &state->rx,
        sampler->hal->read_axis(ES_AXIS_RX),
        ES_DEFAULT_DEADZONE
    );

    es_input_update_axis(
        &state->ry,
        sampler->hal->read_axis(ES_AXIS_RY),
        ES_DEFAULT_DEADZONE
    );

    es_input_finalize(state);
}
