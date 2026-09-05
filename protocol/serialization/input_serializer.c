#include <stdint.h>
#include <stddef.h>

#include "protocol.h"

static void put_u16(
    uint8_t *buffer,
    size_t *offset,
    uint16_t value
) {
    buffer[(*offset)++] = (uint8_t)(value >> 8);
    buffer[(*offset)++] = (uint8_t)(value & 0xFF);
}

static void put_u32(
    uint8_t *buffer,
    size_t *offset,
    uint32_t value
) {
    buffer[(*offset)++] = (uint8_t)(value >> 24);
    buffer[(*offset)++] = (uint8_t)(value >> 16);
    buffer[(*offset)++] = (uint8_t)(value >> 8);
    buffer[(*offset)++] = (uint8_t)(value);
}

size_t es_serialize_input(
    const ES_InputState *state,
    uint8_t *payload
) {
    size_t offset = 0;

    put_u32(payload, &offset, state->buttons);

    put_u16(payload, &offset, state->lx);
    put_u16(payload, &offset, state->ly);

    put_u16(payload, &offset, state->rx);
    put_u16(payload, &offset, state->ry);

    payload[offset++] = state->lt;
    payload[offset++] = state->rt;

    return offset;
}
