#include "reset.h"

void es_reset_init(
    ES_ResetStatus *status
)
{
    status->cause = ES_RESET_UNKNOWN;
    status->count = 0;
    status->valid = 0;
}

void es_reset_record(
    ES_ResetStatus *status,
    ES_ResetCause cause
)
{
    status->cause = cause;
    status->count++;
    status->valid = 1;
}

const char *es_reset_name(
    ES_ResetCause cause
)
{
    switch (cause) {

    case ES_RESET_POWER_ON:
        return "POWER_ON";

    case ES_RESET_EXTERNAL:
        return "EXTERNAL";

    case ES_RESET_BROWNOUT:
        return "BROWNOUT";

    case ES_RESET_WATCHDOG:
        return "WATCHDOG";

    case ES_RESET_SOFTWARE:
        return "SOFTWARE";

    case ES_RESET_FAULT:
        return "FAULT";

    default:
        return "UNKNOWN";
    }
}
