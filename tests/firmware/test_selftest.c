#include <assert.h>
#include <stdio.h>

#include "selftest.h"

int main(void)
{
    ES_SelfTest selftest;

    es_selftest_init(&selftest);

    es_selftest_record(
        &selftest,
        ES_TEST_MEMORY,
        1,
        12
    );

    es_selftest_record(
        &selftest,
        ES_TEST_GPIO,
        1,
        20
    );

    es_selftest_record(
        &selftest,
        ES_TEST_ADC,
        1,
        31
    );

    es_selftest_record(
        &selftest,
        ES_TEST_TIMER,
        1,
        8
    );

    es_selftest_record(
        &selftest,
        ES_TEST_UART,
        1,
        15
    );

    es_selftest_record(
        &selftest,
        ES_TEST_CRC,
        1,
        7
    );

    es_selftest_record(
        &selftest,
        ES_TEST_PROTOCOL,
        1,
        18
    );

    es_selftest_finish(&selftest);

    assert(selftest.complete == 1);
    assert(selftest.all_passed == 1);
    assert(es_selftest_passed(&selftest));

    printf("self-test: PASS\n");

    return 0;
}
