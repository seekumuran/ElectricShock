#ifndef ES_BREADBOARD_BOARD_H
#define ES_BREADBOARD_BOARD_H

#include <stdint.h>

/*
 * Logical pin assignments.
 *
 * These are placeholders and must be mapped to the
 * actual breadboard wiring before flashing.
 */

#define BB_BUTTON_0  0
#define BB_BUTTON_1  1
#define BB_BUTTON_2  2
#define BB_BUTTON_3  3

#define BB_AXIS_LX   0
#define BB_AXIS_LY   1
#define BB_AXIS_RX   2
#define BB_AXIS_RY   3

#define BB_UART_BAUD 115200UL

void bb_board_init(void);

uint8_t bb_read_button(uint8_t index);

uint16_t bb_read_axis(uint8_t axis);

uint32_t bb_millis(void);

void bb_uart_init(uint32_t baudrate);
void bb_uart_write(uint8_t byte);
uint8_t bb_uart_read(void);
uint8_t bb_uart_rx_ready(void);

void bb_watchdog_init(uint32_t timeout_ms);
void bb_watchdog_kick(void);

#endif
