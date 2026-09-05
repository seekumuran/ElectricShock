#ifndef ELECTRIC_SHOCK_CRC16_H
#define ELECTRIC_SHOCK_CRC16_H

#include <stdint.h>
#include <stddef.h>

uint16_t es_crc16(
    const uint8_t *data,
    size_t length
);

#endif
