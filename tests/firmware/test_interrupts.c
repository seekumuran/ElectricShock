#include <assert.h>
#include <stdio.h>

#include "interrupts.h"

static uint32_t timer_calls = 0;
static uint32_t uart_calls = 0;

static void timer_handler(void)
{
    timer_calls++;
}

static void uart_handler(void)
{
    uart_calls++;
}

int main(void)
{
    es_interrupts_init();

    assert(
        es_interrupt_register(
            ES_IRQ_TIMER,
            timer_handler
        )
    );

    assert(
        es_interrupt_register(
            ES_IRQ_UART_RX,
            uart_handler
        )
    );

    es_interrupt_enable(
        ES_IRQ_TIMER
    );

    es_interrupt_enable(
        ES_IRQ_UART_RX
    );

    es_interrupt_dispatch(
        ES_IRQ_TIMER
    );

    es_interrupt_dispatch(
        ES_IRQ_UART_RX
    );

    assert(timer_calls == 1);
    assert(uart_calls == 1);

    es_interrupt_disable(
        ES_IRQ_TIMER
    );

    es_interrupt_dispatch(
        ES_IRQ_TIMER
    );

    assert(timer_calls == 1);

    printf("interrupt tests: PASS\n");

    return 0;
}
