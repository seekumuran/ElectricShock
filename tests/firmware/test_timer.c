#include <assert.h>
#include <stdio.h>

#include "timer.h"

static uint32_t callback_count = 0;

static void timer_callback(void *context)
{
    uint32_t *count = (uint32_t *)context;

    (*count)++;
}

int main(void)
{
    ES_Timer timer;

    es_timer_init(
        &timer,
        1000,
        timer_callback,
        &callback_count
    );

    assert(timer.running == 0);
    assert(timer.tick_count == 0);

    es_timer_start(&timer);

    es_timer_isr(&timer);
    es_timer_isr(&timer);
    es_timer_isr(&timer);

    assert(timer.tick_count == 3);
    assert(callback_count == 3);

    es_timer_stop(&timer);

    es_timer_isr(&timer);

    assert(timer.tick_count == 3);
    assert(callback_count == 3);

    printf("timer tests: PASS\n");

    return 0;
}
