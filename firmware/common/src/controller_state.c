#include "controller_state.h"

#define ES_PACKED_STATE_SIZE 18

static void write_u16_be(
    uint8_t *buffer,
    uint8_t *index,
    uint16_t value
)
{
    buffer[(*index)++] = (uint8_t)(value >> 8);
    buffer[(*index)++] = (uint8_t)(value & 0xFF);
}

static void write_u32_be(
    uint8_t *buffer,
    uint8_t *index,
    uint32_t value
)
{
    buffer[(*index)++] = (uint8_t)(value >> 24);
    buffer[(*index)++] = (uint8_t)(value >> 16);
    buffer[(*index)++] = (uint8_t)(value >> 8);
    buffer[(*index)++] = (uint8_t)value;
}

static uint16_t read_u16_be(
    const uint8_t *buffer,
    uint8_t *index
)
{
    uint16_t value;

    value = ((uint16_t)buffer[(*index)++] << 8);
    value |= buffer[(*index)++];

    return value;
}

static uint32_t read_u32_be(
    const uint8_t *buffer,
    uint8_t *index
)
{
    uint32_t value;

    value = ((uint32_t)buffer[(*index)++] << 24);
    value |= ((uint32_t)buffer[(*index)++] << 16);
    value |= ((uint32_t)buffer[(*index)++] << 8);
    value |= buffer[(*index)++];

    return value;
}

void es_state_pack(
    const ES_ControllerState *input,
    ES_PackedControllerState *output
)
{
    output->version = ES_STATE_VERSION;

    output->buttons = input->button_mask;

    /*
     * Convert signed normalized axis values
     * into unsigned 16-bit wire representation.
     */
    output->lx =
        (uint16_t)((int32_t)input->lx.normalized + 32768);

    output->ly =
        (uint16_t)((int32_t)input->ly.normalized + 32768);

    output->rx =
        (uint16_t)((int32_t)input->rx.normalized + 32768);

    output->ry =
        (uint16_t)((int32_t)input->ry.normalized + 32768);

    output->lt = input->lt;
    output->rt = input->rt;

    output->frame_counter = 0;
}

uint8_t es_state_serialize(
    const ES_PackedControllerState *state,
    uint8_t *buffer
)
{
    uint8_t index = 0;

    buffer[index++] = state->version;

    write_u32_be(
        buffer,
        &index,
        state->buttons
    );

    write_u16_be(
        buffer,
        &index,
        state->lx
    );

    write_u16_be(
        buffer,
        &index,
        state->ly
    );

    write_u16_be(
        buffer,
        &index,
        state->rx
    );

    write_u16_be(
        buffer,
        &index,
        state->ry
    );

    buffer[index++] = state->lt;
    buffer[index++] = state->rt;

    write_u16_be(
        buffer,
        &index,
        state->frame_counter
    );

    return index;
}

uint8_t es_state_deserialize(
    const uint8_t *buffer,
    uint8_t length,
    ES_PackedControllerState *state
)
{
    uint8_t index = 0;

    if (buffer == 0 || state == 0)
        return 0;

    if (length < ES_PACKED_STATE_SIZE)
        return 0;

    state->version = buffer[index++];

    if (state->version != ES_STATE_VERSION)
        return 0;

    state->buttons =
        read_u32_be(buffer, &index);

    state->lx =
        read_u16_be(buffer, &index);

    state->ly =
        read_u16_be(buffer, &index);

    state->rx =
        read_u16_be(buffer, &index);

    state->ry =
        read_u16_be(buffer, &index);

    state->lt = buffer[index++];
    state->rt = buffer[index++];

    state->frame_counter =
        read_u16_be(buffer, &index);

    return 1;
}
