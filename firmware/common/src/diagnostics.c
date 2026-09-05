#include "diagnostics.h"

void es_diag_init(
    ES_Diagnostics *diag
)
{
    diag->tests_run = 0;
    diag->tests_passed = 0;
    diag->tests_failed = 0;

    diag->current_stage = ES_DIAG_BOOT;

    diag->complete = 0;
    diag->fault = 0;
}

void es_diag_begin(
    ES_Diagnostics *diag,
    ES_DiagnosticStage stage
)
{
    diag->current_stage = stage;
    diag->tests_run++;
}

void es_diag_pass(
    ES_Diagnostics *diag
)
{
    diag->tests_passed++;
}

void es_diag_fail(
    ES_Diagnostics *diag
)
{
    diag->tests_failed++;
    diag->fault = 1;
}

void es_diag_complete(
    ES_Diagnostics *diag
)
{
    diag->current_stage = ES_DIAG_COMPLETE;
    diag->complete = 1;
}
