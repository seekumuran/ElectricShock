#ifndef ES_DIAGNOSTICS_H
#define ES_DIAGNOSTICS_H

#include <stdint.h>

typedef enum {
    ES_DIAG_BOOT = 0,
    ES_DIAG_GPIO,
    ES_DIAG_ADC,
    ES_DIAG_TIMER,
    ES_DIAG_UART,
    ES_DIAG_CRC,
    ES_DIAG_PROTOCOL,
    ES_DIAG_WATCHDOG,
    ES_DIAG_MEMORY,
    ES_DIAG_COMPLETE
} ES_DiagnosticStage;

typedef struct {
    uint32_t tests_run;
    uint32_t tests_passed;
    uint32_t tests_failed;

    uint8_t current_stage;
    uint8_t complete;
    uint8_t fault;
} ES_Diagnostics;

void es_diag_init(
    ES_Diagnostics *diag
);

void es_diag_begin(
    ES_Diagnostics *diag,
    ES_DiagnosticStage stage
);

void es_diag_pass(
    ES_Diagnostics *diag
);

void es_diag_fail(
    ES_Diagnostics *diag
);

void es_diag_complete(
    ES_Diagnostics *diag
);

#endif
