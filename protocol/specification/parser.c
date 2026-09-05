#include "parser.h"
#include "crc16.h"

void es_parser_init(
    ES_FrameParser *parser
)
{
    parser->state = ES_PARSE_SYNC;
    parser->payload_index = 0;
    parser->received_crc = 0;

    parser->bytes_processed = 0;
    parser->frames_completed = 0;
    parser->frames_rejected = 0;
}

static void parser_reset(
    ES_FrameParser *parser
)
{
    parser->state = ES_PARSE_SYNC;
    parser->payload_index = 0;
    parser->received_crc = 0;
}

int es_parser_consume(
    ES_FrameParser *parser,
    uint8_t byte,
    ES_Frame *completed_frame
)
{
    parser->bytes_processed++;

    switch (parser->state) {

    case ES_PARSE_SYNC:

        if (byte != ES_SYNC)
            return 0;

        parser->frame.sync = byte;
        parser->state = ES_PARSE_VERSION;
        break;


    case ES_PARSE_VERSION:

        if (byte != ES_VERSION) {
            parser->frames_rejected++;
            parser_reset(parser);
            return 0;
        }

        parser->frame.version = byte;
        parser->state = ES_PARSE_TYPE;
        break;


    case ES_PARSE_TYPE:

        parser->frame.type = byte;
        parser->state = ES_PARSE_SEQ_HIGH;
        break;


    case ES_PARSE_SEQ_HIGH:

        parser->frame.sequence =
            ((uint16_t)byte << 8);

        parser->state = ES_PARSE_SEQ_LOW;
        break;


    case ES_PARSE_SEQ_LOW:

        parser->frame.sequence |= byte;
        parser->state = ES_PARSE_LENGTH;
        break;


    case ES_PARSE_LENGTH:

        if (byte > ES_MAX_PAYLOAD) {
            parser->frames_rejected++;
            parser_reset(parser);
            return 0;
        }

        parser->frame.length = byte;
        parser->payload_index = 0;

        if (byte == 0) {
            parser->state = ES_PARSE_CRC_HIGH;
        } else {
            parser->state = ES_PARSE_PAYLOAD;
        }

        break;


    case ES_PARSE_PAYLOAD:

        parser->frame.payload[
            parser->payload_index++
        ] = byte;

        if (parser->payload_index >=
            parser->frame.length) {

            parser->state = ES_PARSE_CRC_HIGH;
        }

        break;


    case ES_PARSE_CRC_HIGH:

        parser->received_crc =
            ((uint16_t)byte << 8);

        parser->state = ES_PARSE_CRC_LOW;
        break;


    case ES_PARSE_CRC_LOW:
    {
        uint16_t calculated_crc;

        parser->received_crc |= byte;

        calculated_crc = es_crc16(
            (const uint8_t *)&parser->frame,
            6 + parser->frame.length
        );

        parser->frame.crc =
            parser->received_crc;

        if (calculated_crc !=
            parser->received_crc) {

            parser->frames_rejected++;
            parser_reset(parser);
            return 0;
        }

        if (completed_frame != 0)
            *completed_frame = parser->frame;

        parser->frames_completed++;

        parser_reset(parser);

        return 1;
    }

    default:
        parser_reset(parser);
        break;
    }

    return 0;
}
