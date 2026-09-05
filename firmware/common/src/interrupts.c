#include "interrupts.h"

static ES_IRQHandler handlers[ES_IRQ_COUNT];
static uint8_t enabled[ES_IRQ_COUNT];

void es_interrupts_init(void)
{
    uint8_t i;

    for (i = 0; i < ES_IRQ_COUNT; i++) {
        handlers[i] = 0;
        enabled[i] = 0;
    }
}

int es_interrupt_register(
    ES_IRQ irq,
    ES_IRQHandler handler
)
{
    if (irq >= ES_IRQ_COUNT)
        return 0;

    handlers[irq] = handler;

    return 1;
}

void es_interrupt_enable(
    ES_IRQ irq
)
{
    if (irq >= ES_IRQ_COUNT)
        return;

    enabled[irq] = 1;
}

void es_interrupt_disable(
    ES_IRQ irq
)
{
    if (irq >= ES_IRQ_COUNT)
        return;

    enabled[irq] = 0;
}

void es_interrupt_dispatch(
    ES_IRQ irq
)
{
    if (irq >= ES_IRQ_COUNT)
        return;

    if (!enabled[irq])
        return;

    if (handlers[irq] != 0)
        handlers[irq]();
}

uint8_t es_interrupt_is_enabled(
    ES_IRQ irq
)
{
    if (irq >= ES_IRQ_COUNT)
        return 0;

    return enabled[irq];
}
