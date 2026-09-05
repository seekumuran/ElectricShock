#include "crc16.h"

#define CRC16_POLY 0x1021
#define CRC16_INIT 0xFFFF

uint16_t es_crc16(
    const uint8_t *data,
    size_t length
) {
    uint16_t crc = CRC16_INIT;

    for (size_t i = 0; i < length; ++i) {
        crc ^= (uint16_t)data[i] << 8;

        for (uint8_t bit = 0; bit < 8; ++bit) {
            if (crc & 0x8000) {
                crc = (crc << 1) ^ CRC16_POLY;
            } else {
                crc <<= 1;
            }
        }
    }

    return crc;
}
