#include "board.h"

/*
 * Hardware register layer.
 *
 * Replace these definitions with the actual MCU
 * register map when the target is selected.
 */

static volatile uint32_t bb_system_ms = 0;

void bb_board_init(void)
{
    /*
     * GPIO configuration
     * ADC configuration
     * timer configuration
     * UART configuration
     *
     * Target-specific implementation goes here.
     */
}

uint8_t bb_read_button(uint8_t index)
{
    /*
     * Replace with actual GPIO read.
     */

    (void)index;

    return 0;
}

uint16_t bb_read_axis(uint8_t axis)
{
    /*
     * Replace with actual ADC conversion.
     */

    (void)axis;

    return 2048;
}

uint32_t bb_millis(void)
{
    return bb_system_ms;
}

void bb_uart_init(uint32_t baudrate)
{
    (void)baudrate;

    /*
     * Configure UART peripheral here.
     */
}

void bb_uart_write(uint8_t byte)
{
    /*
     * Replace with target UART TX register.
     */

    (void)byte;
}

uint8_t bb_uart_read(void)
{
    /*
     * Replace with target UART RX register.
     */

    return 0;
}

uint8_t bb_uart_rx_ready(void)
{
    /*
     * Replace with UART status flag.
     */

    return 0;
}

void bb_watchdog_init(uint32_t timeout_ms)
{
    (void)timeout_ms;

    /*
     * Configure hardware watchdog.
     */
}

void bb_watchdog_kick(void)
{
    /*
     * Write watchdog service sequence here.
     */
}
