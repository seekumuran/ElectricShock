#ifndef ES_FAULT_H
#define ES_FAULT_H

#include <stdint.h>

typedef enum {
    ES_FAULT_NONE = 0,

    ES_FAULT_BOOT,
    ES_FAULT_MEMORY,
    ES_FAULT_GPIO,
    ES_FAULT_ADC,
    ES_FAULT_UART,
    ES_FAULT_PROTOCOL,
    ES_FAULT_TRANSPORT,
    ES_FAULT_WATCHDOG,
    ES_FAULT_ASSERT,
    ES_FAULT_UNKNOWN
} ES_FaultCode;

typedef enum {
    ES_FAULT_STATE_CLEAR = 0,
    ES_FAULT_STATE_ACTIVE,
    ES_FAULT_STATE_RECOVERED,
    ES_FAULT_STATE_FATAL
} ES_FaultState;

typedef struct {
    ES_FaultCode code;
    ES_FaultState state;

    uint32_t count;
    uint32_t first_seen_ms;
    uint32_t last_seen_ms;

    uint8_t recoverable;
} ES_FaultRecord;

#define ES_MAX_FAULT_RECORDS 16

typedef struct {
    ES_FaultRecord records[ES_MAX_FAULT_RECORDS];

    ES_FaultCode active_fault;

    uint32_t total_faults;
    uint32_t recovered_faults;
    uint32_t fatal_faults;
} ES_FaultManager;

void es_fault_init(
    ES_FaultManager *manager
);

void es_fault_raise(
    ES_FaultManager *manager,
    ES_FaultCode code,
    uint32_t timestamp_ms,
    uint8_t recoverable
);

void es_fault_recover(
    ES_FaultManager *manager,
    ES_FaultCode code,
    uint32_t timestamp_ms
);

uint8_t es_fault_is_active(
    const ES_FaultManager *manager
);

ES_FaultCode es_fault_current(
    const ES_FaultManager *manager
);

const ES_FaultRecord *es_fault_find(
    const ES_FaultManager *manager,
    ES_FaultCode code
);

#endif
