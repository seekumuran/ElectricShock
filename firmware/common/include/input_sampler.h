#ifndef ES_INPUT_SAMPLER_H
#define ES_INPUT_SAMPLER_H

#include <stdint.h>
#include "input.h"
#include "hal.h"

typedef struct {
    ES_Hardware *hal;
    uint8_t button_count;
} ES_InputSampler;

void es_sampler_init(
    ES_InputSampler *sampler,
    ES_Hardware *hal,
    uint8_t button_count
);

void es_sampler_sample(
    ES_InputSampler *sampler,
    ES_ControllerState *state
);

#endif
