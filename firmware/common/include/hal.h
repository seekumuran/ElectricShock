#ifndef ES_HAL_H
#define ES_HAL_H

#include <stdint.h>

typedef struct {
    void (*init)(void);

    uint32_t (*millis)(void);

    uint8_t (*read_button)(uint8_t index);

    uint16_t (*read_axis)(uint8_t axis);

    void (*uart_enable)(uint32_t baudrate);

    void (*uart_write)(uint8_t byte);

    uint8_t (*uart_read)(void);

    uint8_t (*uart_rx_ready)(void);

    void (*watchdog_init)(uint32_t timeout_ms);

    void (*watchdog_kick)(void);
} ES_Hardware;

enum {
    ES_AXIS_LX = 0,
    ES_AXIS_LY = 1,
    ES_AXIS_RX = 2,
    ES_AXIS_RY = 3
};

#endif
