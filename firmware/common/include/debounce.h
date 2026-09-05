#ifndef ES_DEBOUNCE_H
#define ES_DEBOUNCE_H

#include <stdint.h>

typedef struct {
    uint8_t stable;
    uint8_t candidate;
    uint8_t counter;

    uint8_t threshold;
} ES_Debouncer;

void es_debounce_init(
    ES_Debouncer *debouncer,
    uint8_t initial,
    uint8_t threshold
);

uint8_t es_debounce_update(
    ES_Debouncer *debouncer,
    uint8_t sample
);

#endif
