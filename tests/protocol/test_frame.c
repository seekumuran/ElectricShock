#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "../../protocol/specification/frame.h"

static void print_hex(
    const uint8_t *data,
    size_t length
) {
    for (size_t i = 0; i < length; ++i) {
        printf("%02X ", data[i]);
    }

    printf("\n");
}


int main(void) {

    uint8_t payload[] = {
        0x01,
        0x00,
        0x80,
        0x7F,
        0xFF
    };

    uint8_t frame[ES_MAX_FRAME];

    size_t length =
        es_build_frame(
            ES_TYPE_INPUT,
            42,
            payload,
            sizeof(payload),
            frame
        );

    printf("Frame length: %zu\n", length);

    printf("Frame: ");
    print_hex(frame, length);


    ES_Frame decoded;

    ES_FrameResult result =
        es_parse_frame(
            frame,
            length,
            &decoded
        );

    printf(
        "Parser result: %d\n",
        result
    );

    printf(
        "Sequence: %u\n",
        decoded.sequence
    );

    printf(
        "Payload length: %u\n",
        decoded.length
    );

    printf("Payload: ");
    print_hex(
        decoded.payload,
        decoded.length
    );

    return 0;
}
