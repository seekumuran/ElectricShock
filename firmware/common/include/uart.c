#include "uart.h"

void es_uart_init(
    ES_UART *uart,
    ES_Transport *transport,
    uint32_t baudrate
)
{
    uart->transport = transport;

    uart->baudrate = baudrate;

    uart->rx_interrupts = 0;
    uart->tx_interrupts = 0;

    uart->framing_errors = 0;
    uart->overrun_errors = 0;
}

void es_uart_rx_interrupt(
    ES_UART *uart,
    uint8_t byte
)
{
    uart->rx_interrupts++;

    if (!es_transport_rx_push(
            uart->transport,
            byte)) {

        uart->overrun_errors++;
    }
}

int es_uart_tx_interrupt(
    ES_UART *uart,
    uint8_t *byte
)
{
    uart->tx_interrupts++;

    return es_transport_tx_pop(
        uart->transport,
        byte
    );
}
