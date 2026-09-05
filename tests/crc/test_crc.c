#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "../../protocol/crc/crc16.h"

static int test(
    const char *name,
    const uint8_t *data,
    size_t length
) {
    uint16_t crc = es_crc16(data, length);

    printf(
        "[CRC] %-24s -> 0x%04X\n",
        name,
        crc
    );

    return 0;
}


int main(void) {

    static const uint8_t empty[] = {};

    static const uint8_t test1[] = {
        0x00
    };

    static const uint8_t test2[] = {
        0xFF
    };

    static const uint8_t test3[] = {
        0x01,
        0x02,
        0x03,
        0x04
    };

    static const uint8_t test4[] = {
        0xA5,
        0x01,
        0x00,
        0x01,
        0x08,
        0x12,
        0x34,
        0x56,
        0x78
    };

    test("empty", empty, 0);
    test("zero", test1, sizeof(test1));
    test("0xFF", test2, sizeof(test2));
    test("incrementing", test3, sizeof(test3));
    test("controller frame", test4, sizeof(test4));

    return 0;
}
