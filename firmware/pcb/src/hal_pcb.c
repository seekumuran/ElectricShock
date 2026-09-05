#include "hal.h"
#include "board.h"

static void pcb_hal_init(void)
{
    pcb_board_init();
}

static uint32_t pcb_hal_millis(void)
{
    return pcb_millis();
}

static uint8_t pcb_hal_read_button(uint8_t index)
{
    return pcb_read_button(index);
}

static uint16_t pcb_hal_read_axis(uint8_t axis)
{
    return pcb_read_axis(axis);
}

static void pcb_hal_uart_enable(uint32_t baudrate)
{
    pcb_uart_init(baudrate);
}

static void pcb_hal_uart_write(uint8_t byte)
{
    pcb_uart_write(byte);
}

static uint8_t pcb_hal_uart_read(void)
{
    return pcb_uart_read();
}

static uint8_t pcb_hal_uart_rx_ready(void)
{
    return pcb_uart_rx_ready();
}

static void pcb_hal_watchdog_init(uint32_t timeout_ms)
{
    pcb_watchdog_init(timeout_ms);
}

static void pcb_hal_watchdog_kick(void)
{
    pcb_watchdog_kick();
}

ES_Hardware es_pcb_hal = {
    .init = pcb_hal_init,
    .millis = pcb_hal_millis,

    .read_button = pcb_hal_read_button,
    .read_axis = pcb_hal_read_axis,

    .uart_enable = pcb_hal_uart_enable,
    .uart_write = pcb_hal_uart_write,
    .uart_read = pcb_hal_uart_read,
    .uart_rx_ready = pcb_hal_uart_rx_ready,

    .watchdog_init = pcb_hal_watchdog_init,
    .watchdog_kick = pcb_hal_watchdog_kick
};
