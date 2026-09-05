#ifndef ES_CONTROLLER_STATE_H
#define ES_CONTROLLER_STATE_H

#include <stdint.h>
#include "input.h"

#define ES_STATE_VERSION 1

typedef struct {
    uint8_t version;

    uint32_t buttons;

    uint16_t lx;
    uint16_t ly;
    uint16_t rx;
    uint16_t ry;

    uint8_t lt;
    uint8_t rt;

    uint16_t frame_counter;
} ES_PackedControllerState;

/*
 * Convert processed controller input into
 * the compact protocol representation.
 */
void es_state_pack(
    const ES_ControllerState *input,
    ES_PackedControllerState *output
);

/*
 * Serialize the packed state into a byte buffer.
 */
uint8_t es_state_serialize(
    const ES_PackedControllerState *state,
    uint8_t *buffer
);

/*
 * Deserialize a controller state payload.
 */
uint8_t es_state_deserialize(
    const uint8_t *buffer,
    uint8_t length,
    ES_PackedControllerState *state
);

#endif
