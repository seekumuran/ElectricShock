#include "fault.h"

static ES_FaultRecord *find_record(
    ES_FaultManager *manager,
    ES_FaultCode code
)
{
    uint8_t i;

    for (i = 0; i < ES_MAX_FAULT_RECORDS; i++) {
        if (manager->records[i].code == code)
            return &manager->records[i];
    }

    return 0;
}

static ES_FaultRecord *allocate_record(
    ES_FaultManager *manager,
    ES_FaultCode code
)
{
    uint8_t i;

    for (i = 0; i < ES_MAX_FAULT_RECORDS; i++) {
        if (manager->records[i].code ==
            ES_FAULT_NONE) {

            manager->records[i].code = code;
            return &manager->records[i];
        }
    }

    return 0;
}

void es_fault_init(
    ES_FaultManager *manager
)
{
    uint8_t i;

    for (i = 0; i < ES_MAX_FAULT_RECORDS; i++) {
        manager->records[i].code = ES_FAULT_NONE;
        manager->records[i].state =
            ES_FAULT_STATE_CLEAR;

        manager->records[i].count = 0;
        manager->records[i].first_seen_ms = 0;
        manager->records[i].last_seen_ms = 0;

        manager->records[i].recoverable = 0;
    }

    manager->active_fault = ES_FAULT_NONE;

    manager->total_faults = 0;
    manager->recovered_faults = 0;
    manager->fatal_faults = 0;
}

void es_fault_raise(
    ES_FaultManager *manager,
    ES_FaultCode code,
    uint32_t timestamp_ms,
    uint8_t recoverable
)
{
    ES_FaultRecord *record;

    if (code == ES_FAULT_NONE)
        return;

    record = find_record(manager, code);

    if (record == 0)
        record = allocate_record(manager, code);

    if (record == 0) {
        manager->fatal_faults++;
        manager->active_fault =
            ES_FAULT_UNKNOWN;
        return;
    }

    if (record->count == 0)
        record->first_seen_ms = timestamp_ms;

    record->count++;
    record->last_seen_ms = timestamp_ms;

    record->recoverable = recoverable;
    record->state = ES_FAULT_STATE_ACTIVE;

    manager->active_fault = code;
    manager->total_faults++;

    if (!recoverable)
        manager->fatal_faults++;
}

void es_fault_recover(
    ES_FaultManager *manager,
    ES_FaultCode code,
    uint32_t timestamp_ms
)
{
    ES_FaultRecord *record;

    record = find_record(manager, code);

    if (record == 0)
        return;

    record->last_seen_ms = timestamp_ms;

    if (record->state ==
        ES_FAULT_STATE_ACTIVE) {

        record->state =
            ES_FAULT_STATE_RECOVERED;

        manager->recovered_faults++;

        if (manager->active_fault == code)
            manager->active_fault =
                ES_FAULT_NONE;
    }
}

uint8_t es_fault_is_active(
    const ES_FaultManager *manager
)
{
    return manager->active_fault !=
           ES_FAULT_NONE;
}

ES_FaultCode es_fault_current(
    const ES_FaultManager *manager
)
{
    return manager->active_fault;
}

const ES_FaultRecord *es_fault_find(
    const ES_FaultManager *manager,
    ES_FaultCode code
)
{
    uint8_t i;

    for (i = 0; i < ES_MAX_FAULT_RECORDS; i++) {
        if (manager->records[i].code == code)
            return &manager->records[i];
    }

    return 0;
}
