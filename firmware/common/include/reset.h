#ifndef ES_RESET_H
#define ES_RESET_H

#include <stdint.h>

typedef enum {
    ES_RESET_UNKNOWN = 0,
    ES_RESET_POWER_ON,
    ES_RESET_EXTERNAL,
    ES_RESET_BROWNOUT,
    ES_RESET_WATCHDOG,
    ES_RESET_SOFTWARE,
    ES_RESET_FAULT
} ES_ResetCause;

typedef struct {
    ES_ResetCause cause;
    uint32_t count;
    uint8_t valid;
} ES_ResetStatus;

void es_reset_init(
    ES_ResetStatus *status
);

void es_reset_record(
    ES_ResetStatus *status,
    ES_ResetCause cause
);

const char *es_reset_name(
    ES_ResetCause cause
);

#endif
