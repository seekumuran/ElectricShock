#include <assert.h>
#include <stdio.h>

#include "diagnostics.h"

int main(void)
{
    ES_Diagnostics diag;

    es_diag_init(&diag);

    assert(diag.tests_run == 0);
    assert(diag.tests_passed == 0);
    assert(diag.tests_failed == 0);
    assert(diag.complete == 0);

    es_diag_begin(
        &diag,
        ES_DIAG_GPIO
    );

    es_diag_pass(&diag);

    es_diag_begin(
        &diag,
        ES_DIAG_ADC
    );

    es_diag_pass(&diag);

    es_diag_begin(
        &diag,
        ES_DIAG_UART
    );

    es_diag_fail(&diag);

    assert(diag.tests_run == 3);
    assert(diag.tests_passed == 2);
    assert(diag.tests_failed == 1);
    assert(diag.fault == 1);

    es_diag_complete(&diag);

    assert(diag.complete == 1);
    assert(
        diag.current_stage == ES_DIAG_COMPLETE
    );

    printf("diagnostics tests: PASS\n");

    return 0;
}
