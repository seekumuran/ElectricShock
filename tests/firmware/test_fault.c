#include <assert.h>
#include <stdio.h>

#include "fault.h"

int main(void)
{
    ES_FaultManager manager;

    es_fault_init(&manager);

    assert(
        !es_fault_is_active(&manager)
    );

    es_fault_raise(
        &manager,
        ES_FAULT_UART,
        100,
        1
    );

    assert(
        es_fault_is_active(&manager)
    );

    assert(
        es_fault_current(&manager)
        == ES_FAULT_UART
    );

    const ES_FaultRecord *record =
        es_fault_find(
            &manager,
            ES_FAULT_UART
        );

    assert(record != 0);
    assert(record->count == 1);
    assert(record->recoverable == 1);

    es_fault_recover(
        &manager,
        ES_FAULT_UART,
        150
    );

    assert(
        !es_fault_is_active(&manager)
    );

    assert(
        record->state ==
        ES_FAULT_STATE_RECOVERED
    );

    printf("fault tests: PASS\n");

    return 0;
}
