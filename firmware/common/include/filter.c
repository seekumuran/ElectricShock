#include "filter.h"

void es_filter_init(
    ES_LowPassFilter *filter,
    int32_t initial,
    uint8_t shift
)
{
    filter->value = initial;
    filter->shift = shift;
}

int32_t es_filter_update(
    ES_LowPassFilter *filter,
    int32_t sample
)
{
    int32_t delta;

    delta = sample - filter->value;

    filter->value +=
        delta >> filter->shift;

    return filter->value;
}
