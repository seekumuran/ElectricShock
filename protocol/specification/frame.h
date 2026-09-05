#ifndef ELECTRIC_SHOCK_FRAME_H
#define ELECTRIC_SHOCK_FRAME_H

#include <stdint.h>
#include <stddef.h>

#include "protocol.h"

#define ES_FRAME_HEADER_SIZE 6
#define ES_FRAME_CRC_SIZE    2

typedef enum {
    ES_FRAME_OK = 0,
    ES_FRAME_TOO_SHORT,
    ES_FRAME_BAD_SYNC,
    ES_FRAME_BAD_VERSION,
    ES_FRAME_BAD_LENGTH,
    ES_FRAME_BAD_CRC
} ES_FrameResult;

size_t es_build_frame(
    uint8_t type,
    uint16_t sequence,
    const uint8_t *payload,
    uint8_t payload_length,
    uint8_t *frame
);

ES_FrameResult es_parse_frame(
    const uint8_t *frame,
    size_t frame_length,
    ES_Frame *output
);

#endif
