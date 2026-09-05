#include "watchdog.h"

void es_watchdog_init(
    ES_Watchdog *watchdog,
    uint32_t timeout_ms
)
{
    watchdog->timeout_ms = timeout_ms;
    watchdog->kicks = 0;
    watchdog->enabled = 1;
}

void es_watchdog_kick(
    ES_Watchdog *watchdog
)
{
    if (!watchdog->enabled)
        return;

    watchdog->kicks++;
}
