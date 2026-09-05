#ifndef ES_INPUT_H
#define ES_INPUT_H

#include <stdint.h>

#define ES_BUTTON_COUNT 16

#define ES_AXIS_MIN     0
#define ES_AXIS_MAX     4095
#define ES_AXIS_CENTER  2048

#define ES_DEFAULT_DEADZONE 180

typedef struct {
    uint8_t raw;
    uint8_t stable;
    uint8_t previous;
    uint8_t pressed;
    uint8_t released;
} ES_ButtonState;

typedef struct {
    uint16_t raw;
    int16_t centered;
    int16_t filtered;
    int16_t normalized;
} ES_AxisState;

typedef struct {
    ES_ButtonState buttons[ES_BUTTON_COUNT];

    ES_AxisState lx;
    ES_AxisState ly;
    ES_AxisState rx;
    ES_AxisState ry;

    uint8_t lt;
    uint8_t rt;

    uint32_t button_mask;
} ES_ControllerState;

void es_input_init(ES_ControllerState *state);

void es_input_update_button(
    ES_ControllerState *state,
    uint8_t index,
    uint8_t raw
);

void es_input_update_axis(
    ES_AxisState *axis,
    uint16_t raw,
    int16_t deadzone
);

void es_input_update_triggers(
    ES_ControllerState *state,
    uint8_t lt,
    uint8_t rt
);

void es_input_finalize(ES_ControllerState *state);

#endif
