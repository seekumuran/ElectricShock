#ifndef ES_UART_H
#define ES_UART_H

#include <stdint.h>
#include "transport.h"

typedef struct {
    ES_Transport *transport;

    uint32_t baudrate;

    uint32_t rx_interrupts;
    uint32_t tx_interrupts;

    uint32_t framing_errors;
    uint32_t overrun_errors;
} ES_UART;

void es_uart_init(
    ES_UART *uart,
    ES_Transport *transport,
    uint32_t baudrate
);

void es_uart_rx_interrupt(
    ES_UART *uart,
    uint8_t byte
);

int es_uart_tx_interrupt(
    ES_UART *uart,
    uint8_t *byte
);

#endif
