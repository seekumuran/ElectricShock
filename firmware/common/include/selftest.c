#include "selftest.h"

void es_selftest_init(
    ES_SelfTest *selftest
)
{
    uint8_t i;

    for (i = 0; i < ES_TEST_COUNT; i++) {
        selftest->tests[i].executed = 0;
        selftest->tests[i].passed = 0;
        selftest->tests[i].duration_us = 0;
    }

    selftest->complete = 0;
    selftest->all_passed = 0;
    selftest->total_duration_us = 0;
}

void es_selftest_record(
    ES_SelfTest *selftest,
    ES_TestId test,
    uint8_t passed,
    uint32_t duration_us
)
{
    if (test >= ES_TEST_COUNT)
        return;

    selftest->tests[test].executed = 1;
    selftest->tests[test].passed =
        passed ? 1 : 0;

    selftest->tests[test].duration_us =
        duration_us;

    selftest->total_duration_us +=
        duration_us;
}

void es_selftest_finish(
    ES_SelfTest *selftest
)
{
    uint8_t i;

    selftest->complete = 1;
    selftest->all_passed = 1;

    for (i = 0; i < ES_TEST_COUNT; i++) {

        if (!selftest->tests[i].executed ||
            !selftest->tests[i].passed) {

            selftest->all_passed = 0;
            break;
        }
    }
}

uint8_t es_selftest_passed(
    const ES_SelfTest *selftest
)
{
    return selftest->complete &&
           selftest->all_passed;
}
