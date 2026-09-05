#ifndef ELECTRIC_SHOCK_PROTOCOL_H
#define ELECTRIC_SHOCK_PROTOCOL_H

#include <stdint.h>

#define ES_SYNC             0xA5
#define ES_VERSION          0x01

#define ES_TYPE_INPUT       0x01
#define ES_TYPE_STATUS      0x02
#define ES_TYPE_ACK         0x06
#define ES_TYPE_ERROR       0x15

#define ES_MAX_PAYLOAD      32
#define ES_FRAME_OVERHEAD   8
#define ES_MAX_FRAME        (ES_MAX_PAYLOAD + ES_FRAME_OVERHEAD)

/*
 * Input payload
 *
 * buttons : 32-bit button bitmap
 * lx      : left stick X
 * ly      : left stick Y
 * rx      : right stick X
 * ry      : right stick Y
 * lt      : left trigger
 * rt      : right trigger
 */

typedef struct {
    uint32_t buttons;

    uint16_t lx;
    uint16_t ly;

    uint16_t rx;
    uint16_t ry;

    uint8_t lt;
    uint8_t rt;
} ES_InputState;


typedef struct {
    uint8_t  sync;
    uint8_t  version;
    uint8_t  type;

    uint16_t sequence;

    uint8_t  length;

    uint8_t  payload[ES_MAX_PAYLOAD];

    uint16_t crc;
} ES_Frame;

#endif
