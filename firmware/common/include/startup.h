#ifndef ES_STARTUP_H
#define ES_STARTUP_H

#include <stdint.h>

typedef enum {
    ES_STARTUP_RESET = 0,
    ES_STARTUP_STACK,
    ES_STARTUP_DATA,
    ES_STARTUP_BSS,
    ES_STARTUP_CLOCK,
    ES_STARTUP_PERIPHERALS,
    ES_STARTUP_RUNTIME,
    ES_STARTUP_SELFTEST,
    ES_STARTUP_COMPLETE,
    ES_STARTUP_FAILED
} ES_StartupStage;

typedef struct {
    ES_StartupStage stage;

    uint32_t stage_count;

    uint8_t stack_ready;
    uint8_t data_ready;
    uint8_t bss_ready;
    uint8_t clock_ready;
    uint8_t peripherals_ready;
    uint8_t runtime_ready;
    uint8_t selftest_ready;

    uint8_t complete;
    uint8_t failed;
} ES_Startup;

void es_startup_init(
    ES_Startup *startup
);

void es_startup_enter(
    ES_Startup *startup,
    ES_StartupStage stage
);

void es_startup_success(
    ES_Startup *startup
);

void es_startup_fail(
    ES_Startup *startup
);

uint8_t es_startup_ready(
    const ES_Startup *startup
);

#endif
