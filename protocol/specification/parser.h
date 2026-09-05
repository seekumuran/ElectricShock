#ifndef ES_PARSER_H
#define ES_PARSER_H

#include <stdint.h>
#include "protocol.h"

typedef enum {
    ES_PARSE_SYNC,
    ES_PARSE_VERSION,
    ES_PARSE_TYPE,
    ES_PARSE_SEQ_HIGH,
    ES_PARSE_SEQ_LOW,
    ES_PARSE_LENGTH,
    ES_PARSE_PAYLOAD,
    ES_PARSE_CRC_HIGH,
    ES_PARSE_CRC_LOW
} ES_ParseState;

typedef struct {
    ES_ParseState state;

    ES_Frame frame;

    uint8_t payload_index;

    uint16_t received_crc;

    uint32_t bytes_processed;
    uint32_t frames_completed;
    uint32_t frames_rejected;
} ES_FrameParser;

void es_parser_init(
    ES_FrameParser *parser
);

int es_parser_consume(
    ES_FrameParser *parser,
    uint8_t byte,
    ES_Frame *completed_frame
);

#endif
