#ifndef ES_WATCHDOG_H
#define ES_WATCHDOG_H

#include <stdint.h>

typedef struct {
    uint32_t timeout_ms;
    uint32_t kicks;
    uint8_t enabled;
} ES_Watchdog;

void es_watchdog_init(
    ES_Watchdog *watchdog,
    uint32_t timeout_ms
);

void es_watchdog_kick(
    ES_Watchdog *watchdog
);

#endif
