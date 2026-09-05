#ifndef ES_FILTER_H
#define ES_FILTER_H

#include <stdint.h>

typedef struct {
    int32_t value;
    uint8_t shift;
} ES_LowPassFilter;

void es_filter_init(
    ES_LowPassFilter *filter,
    int32_t initial,
    uint8_t shift
);

int32_t es_filter_update(
    ES_LowPassFilter *filter,
    int32_t sample
);

#endif
