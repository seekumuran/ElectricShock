#ifndef ES_RUNTIME_H
#define ES_RUNTIME_H

#include <stdint.h>

#include "input.h"
#include "transport.h"
#include "parser.h"

#define ES_INPUT_PERIOD_MS       1
#define ES_FRAME_PERIOD_MS       4
#define ES_HEARTBEAT_PERIOD_MS   1000
#define ES_RX_TIMEOUT_MS         100

typedef struct {
    uint32_t uptime_ms;

    uint32_t input_ticks;
    uint32_t frame_ticks;
    uint32_t heartbeat_ticks;

    uint32_t frames_generated;
    uint32_t frames_transmitted;
    uint32_t frames_received;

    uint32_t parser_errors;
    uint32_t transport_errors;

    uint8_t communication_alive;
    uint8_t fault;
} ES_RuntimeStats;

typedef struct {
    ES_ControllerState input;
    ES_Transport transport;
    ES_FrameParser parser;

    ES_RuntimeStats stats;

    uint16_t sequence;

    uint32_t next_input_tick;
    uint32_t next_frame_tick;
    uint32_t next_heartbeat_tick;

    uint32_t last_rx_tick;
} ES_Runtime;

void es_runtime_init(
    ES_Runtime *runtime
);

void es_runtime_tick(
    ES_Runtime *runtime,
    uint32_t now_ms
);

void es_runtime_rx_byte(
    ES_Runtime *runtime,
    uint8_t byte
);

uint16_t es_runtime_get_sequence(
    const ES_Runtime *runtime
);

#endif
