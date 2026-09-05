#include <string.h>

#include "frame.h"
#include "../crc/crc16.h"

static void write_u16(
    uint8_t *p,
    uint16_t value
) {
    p[0] = (uint8_t)(value >> 8);
    p[1] = (uint8_t)(value & 0xFF);
}

static uint16_t read_u16(
    const uint8_t *p
) {
    return ((uint16_t)p[0] << 8) |
           ((uint16_t)p[1]);
}


size_t es_build_frame(
    uint8_t type,
    uint16_t sequence,
    const uint8_t *payload,
    uint8_t payload_length,
    uint8_t *frame
) {
    if (payload_length > ES_MAX_PAYLOAD) {
        return 0;
    }

    frame[0] = ES_SYNC;
    frame[1] = ES_VERSION;
    frame[2] = type;

    write_u16(
        &frame[3],
        sequence
    );

    frame[5] = payload_length;

    memcpy(
        &frame[6],
        payload,
        payload_length
    );

    size_t crc_offset =
        ES_FRAME_HEADER_SIZE + payload_length;

    uint16_t crc =
        es_crc16(
            frame,
            crc_offset
        );

    write_u16(
        &frame[crc_offset],
        crc
    );

    return crc_offset + ES_FRAME_CRC_SIZE;
}


ES_FrameResult es_parse_frame(
    const uint8_t *frame,
    size_t frame_length,
    ES_Frame *output
) {
    if (frame_length < 8) {
        return ES_FRAME_TOO_SHORT;
    }

    if (frame[0] != ES_SYNC) {
        return ES_FRAME_BAD_SYNC;
    }

    if (frame[1] != ES_VERSION) {
        return ES_FRAME_BAD_VERSION;
    }

    uint8_t payload_length = frame[5];

    if (payload_length > ES_MAX_PAYLOAD) {
        return ES_FRAME_BAD_LENGTH;
    }

    size_t expected_length =
        ES_FRAME_HEADER_SIZE +
        payload_length +
        ES_FRAME_CRC_SIZE;

    if (frame_length != expected_length) {
        return ES_FRAME_BAD_LENGTH;
    }

    uint16_t calculated_crc =
        es_crc16(
            frame,
            ES_FRAME_HEADER_SIZE + payload_length
        );

    uint16_t received_crc =
        read_u16(
            &frame[ES_FRAME_HEADER_SIZE + payload_length]
        );

    if (calculated_crc != received_crc) {
        return ES_FRAME_BAD_CRC;
    }

    output->sync = frame[0];
    output->version = frame[1];
    output->type = frame[2];

    output->sequence =
        read_u16(&frame[3]);

    output->length = payload_length;

    memcpy(
        output->payload,
        &frame[6],
        payload_length
    );

    output->crc = received_crc;

    return ES_FRAME_OK;
}
