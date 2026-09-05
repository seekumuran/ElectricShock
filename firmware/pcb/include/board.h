#ifndef ES_PCB_BOARD_H
#define ES_PCB_BOARD_H

#include <stdint.h>

#define PCB_UART_BAUD 115200UL

#define PCB_AXIS_LX   0
#define PCB_AXIS_LY   1
#define PCB_AXIS_RX   2
#define PCB_AXIS_RY   3

void pcb_board_init(void);

uint8_t pcb_read_button(uint8_t index);
uint16_t pcb_read_axis(uint8_t axis);

uint32_t pcb_millis(void);

void pcb_uart_init(uint32_t baudrate);
void pcb_uart_write(uint8_t byte);
uint8_t pcb_uart_read(void);
uint8_t pcb_uart_rx_ready(void);

void pcb_watchdog_init(uint32_t timeout_ms);
void pcb_watchdog_kick(void);

#endif
