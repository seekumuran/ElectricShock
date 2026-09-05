#ifndef ELECTRIC_SHOCK_SERIALIZER_H
#define ELECTRIC_SHOCK_SERIALIZER_H

#include <stdint.h>
#include <stddef.h>

#include "protocol.h"

size_t es_serialize_input(
    const ES_InputState *state,
    uint8_t *payload
);

#endif
