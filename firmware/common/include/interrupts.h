#ifndef ES_INTERRUPTS_H
#define ES_INTERRUPTS_H

#include <stdint.h>

typedef enum {
    ES_IRQ_TIMER = 0,
    ES_IRQ_UART_RX,
    ES_IRQ_UART_TX,
    ES_IRQ_ADC,
    ES_IRQ_GPIO,
    ES_IRQ_WATCHDOG,
    ES_IRQ_COUNT
} ES_IRQ;

typedef void (*ES_IRQHandler)(void);

void es_interrupts_init(void);

int es_interrupt_register(
    ES_IRQ irq,
    ES_IRQHandler handler
);

void es_interrupt_enable(
    ES_IRQ irq
);

void es_interrupt_disable(
    ES_IRQ irq
);

void es_interrupt_dispatch(
    ES_IRQ irq
);

uint8_t es_interrupt_is_enabled(
    ES_IRQ irq
);

#endif
