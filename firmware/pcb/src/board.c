#include "board.h"

static volatile uint32_t pcb_system_ms = 0;

void pcb_board_init(void)
{
    /*
     * PCB-specific initialization.
     *
     * GPIO
     * ADC
     * timer
     * UART
     * watchdog
     */
}

uint8_t pcb_read_button(uint8_t index)
{
    (void)index;

    return 0;
}

uint16_t pcb_read_axis(uint8_t axis)
{
    (void)axis;

    return 2048;
}

uint32_t pcb_millis(void)
{
    return pcb_system_ms;
}

void pcb_uart_init(uint32_t baudrate)
{
    (void)baudrate;
}

void pcb_uart_write(uint8_t byte)
{
    (void)byte;
}

uint8_t pcb_uart_read(void)
{
    return 0;
}

uint8_t pcb_uart_rx_ready(void)
{
    return 0;
}

void pcb_watchdog_init(uint32_t timeout_ms)
{
    (void)timeout_ms;
}

void pcb_watchdog_kick(void)
{
}
