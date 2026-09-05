#ifndef ELECTRIC_SHOCK_SEQUENCE_H
#define ELECTRIC_SHOCK_SEQUENCE_H

#include <stdint.h>

typedef enum {
    ES_SEQUENCE_FIRST,
    ES_SEQUENCE_NEXT,
    ES_SEQUENCE_DUPLICATE,
    ES_SEQUENCE_LOST
} ES_SequenceResult;

typedef struct {
    uint16_t expected;
    uint8_t initialized;
} ES_SequenceTracker;

void es_sequence_init(
    ES_SequenceTracker *tracker
);

ES_SequenceResult es_sequence_check(
    ES_SequenceTracker *tracker,
    uint16_t sequence
);

#endif
