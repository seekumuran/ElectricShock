#include "debounce.h"

void es_debounce_init(
    ES_Debouncer *debouncer,
    uint8_t initial,
    uint8_t threshold
)
{
    debouncer->stable = initial ? 1 : 0;
    debouncer->candidate = debouncer->stable;
    debouncer->counter = 0;

    debouncer->threshold =
        threshold == 0 ? 1 : threshold;
}

uint8_t es_debounce_update(
    ES_Debouncer *debouncer,
    uint8_t sample
)
{
    sample = sample ? 1 : 0;

    if (sample == debouncer->stable) {
        debouncer->candidate = sample;
        debouncer->counter = 0;
        return debouncer->stable;
    }

    if (sample != debouncer->candidate) {
        debouncer->candidate = sample;
        debouncer->counter = 1;
        return debouncer->stable;
    }

    if (debouncer->counter < debouncer->threshold)
        debouncer->counter++;

    if (debouncer->counter >= debouncer->threshold) {
        debouncer->stable = debouncer->candidate;
        debouncer->counter = 0;
    }

    return debouncer->stable;
}
