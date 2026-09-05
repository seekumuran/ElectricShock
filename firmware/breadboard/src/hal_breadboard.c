#include "hal.h"
#include "board.h"

static void hal_init(void)
{
    bb_board_init();
}

static uint32_t hal_millis(void)
{
    return bb_millis();
}

static uint8_t hal_read_button(uint8_t index)
{
    return bb_read_button(index);
}

static uint16_t hal_read_axis(uint8_t axis)
{
    return bb_read_axis(axis);
}

static void hal_uart_enable(uint32_t baudrate)
{
    bb_uart_init(baudrate);
}

static void hal_uart_write(uint8_t byte)
{
    bb_uart_write(byte);
}

static uint8_t hal_uart_read(void)
{
    return bb_uart_read();
}

static uint8_t hal_uart_rx_ready(void)
{
    return bb_uart_rx_ready();
}

static void hal_watchdog_init(uint32_t timeout_ms)
{
    bb_watchdog_init(timeout_ms);
}

static void hal_watchdog_kick(void)
{
    bb_watchdog_kick();
}

ES_Hardware es_breadboard_hal = {
    .init = hal_init,
    .millis = hal_millis,

    .read_button = hal_read_button,
    .read_axis = hal_read_axis,

    .uart_enable = hal_uart_enable,
    .uart_write = hal_uart_write,
    .uart_read = hal_uart_read,
    .uart_rx_ready = hal_uart_rx_ready,

    .watchdog_init = hal_watchdog_init,
    .watchdog_kick = hal_watchdog_kick
};
