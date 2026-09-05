#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "../../protocol/crc/crc16.h"

static void flip_bit(
    uint8_t *data,
    size_t byte,
    uint8_t bit
) {
    data[byte] ^= (uint8_t)(1u << bit);
}


int main(void) {

    uint8_t frame[] = {
        0xA5,
        0x01,
        0x00,
        0x01,
        0x08,
        0x10,
        0x20,
        0x30,
        0x40
    };

    uint16_t original =
        es_crc16(frame, sizeof(frame));

    printf(
        "Original CRC : 0x%04X\n",
        original
    );


    /*
     * Single-bit corruption
     */

    for (uint8_t bit = 0; bit < 8; ++bit) {

        uint8_t corrupted[
            sizeof(frame)
        ];

        memcpy(
            corrupted,
            frame,
            sizeof(frame)
        );

        flip_bit(
            corrupted,
            5,
            bit
        );

        uint16_t crc =
            es_crc16(
                corrupted,
                sizeof(corrupted)
            );

        printf(
            "Bit %u corruption -> 0x%04X %s\n",
            bit,
            crc,
            crc != original
                ? "DETECTED"
                : "MISSED"
        );
    }

    return 0;
}
