#ifndef ES_TIMER_H
#define ES_TIMER_H

#include <stdint.h>

typedef void (*ES_TimerCallback)(void *context);

typedef struct {
    uint32_t frequency_hz;
    uint32_t tick_count;
    uint8_t running;

    ES_TimerCallback callback;
    void *context;
} ES_Timer;

void es_timer_init(
    ES_Timer *timer,
    uint32_t frequency_hz,
    ES_TimerCallback callback,
    void *context
);

void es_timer_start(
    ES_Timer *timer
);

void es_timer_stop(
    ES_Timer *timer
);

void es_timer_isr(
    ES_Timer *timer
);

uint32_t es_timer_ticks(
    const ES_Timer *timer
);

#endif
