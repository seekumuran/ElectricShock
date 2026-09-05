#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "../../protocol/specification/frame.h"

int main(void) {

    uint8_t payload[] = {
        0x11,
        0x22,
        0x33,
        0x44
    };

    uint8_t frame[ES_MAX_FRAME];

    size_t length =
        es_build_frame(
            ES_TYPE_INPUT,
            100,
            payload,
            sizeof(payload),
            frame
        );


    /*
     * Corrupt payload.
     */

    frame[7] ^= 0x01;


    ES_Frame decoded;

    ES_FrameResult result =
        es_parse_frame(
            frame,
            length,
            &decoded
        );


    if (result == ES_FRAME_BAD_CRC) {

        printf(
            "PASS: payload corruption detected\n"
        );

        return 0;
    }


    printf(
        "FAIL: corruption was not detected\n"
    );

    return 1;
}
