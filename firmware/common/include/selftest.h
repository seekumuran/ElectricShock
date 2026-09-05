#ifndef ES_SELFTEST_H
#define ES_SELFTEST_H

#include <stdint.h>

typedef enum {
    ES_TEST_MEMORY = 0,
    ES_TEST_GPIO,
    ES_TEST_ADC,
    ES_TEST_TIMER,
    ES_TEST_UART,
    ES_TEST_CRC,
    ES_TEST_PROTOCOL,
    ES_TEST_COUNT
} ES_TestId;

typedef struct {
    uint8_t executed;
    uint8_t passed;
    uint32_t duration_us;
} ES_TestResult;

typedef struct {
    ES_TestResult tests[ES_TEST_COUNT];

    uint8_t complete;
    uint8_t all_passed;

    uint32_t total_duration_us;
} ES_SelfTest;

void es_selftest_init(
    ES_SelfTest *selftest
);

void es_selftest_record(
    ES_SelfTest *selftest,
    ES_TestId test,
    uint8_t passed,
    uint32_t duration_us
);

void es_selftest_finish(
    ES_SelfTest *selftest
);

uint8_t es_selftest_passed(
    const ES_SelfTest *selftest
);

#endif
