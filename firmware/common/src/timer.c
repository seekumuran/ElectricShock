#include "timer.h"

void es_timer_init(
    ES_Timer *timer,
    uint32_t frequency_hz,
    ES_TimerCallback callback,
    void *context
)
{
    timer->frequency_hz = frequency_hz;
    timer->tick_count = 0;
    timer->running = 0;

    timer->callback = callback;
    timer->context = context;
}

void es_timer_start(
    ES_Timer *timer
)
{
    timer->running = 1;
}

void es_timer_stop(
    ES_Timer *timer
)
{
    timer->running = 0;
}

void es_timer_isr(
    ES_Timer *timer
)
{
    if (!timer->running)
        return;

    timer->tick_count++;

    if (timer->callback != 0)
        timer->callback(timer->context);
}

uint32_t es_timer_ticks(
    const ES_Timer *timer
)
{
    return timer->tick_count;
}
