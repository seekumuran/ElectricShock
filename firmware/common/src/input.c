#include "input.h"

static int16_t clamp_i16(int16_t value, int16_t min, int16_t max)
{
    if (value < min)
        return min;

    if (value > max)
        return max;

    return value;
}

static int16_t normalize_axis(int16_t value, int16_t deadzone)
{
    int32_t magnitude;
    int32_t range;
    int32_t normalized;

    value = clamp_i16(
        value,
        -(ES_AXIS_CENTER),
        ES_AXIS_MAX - ES_AXIS_CENTER
    );

    magnitude = value < 0 ? -value : value;

    if (magnitude <= deadzone)
        return 0;

    if (value > 0) {
        range = (ES_AXIS_MAX - ES_AXIS_CENTER) - deadzone;

        normalized =
            ((magnitude - deadzone) * 32767) / range;
    } else {
        range = ES_AXIS_CENTER - deadzone;

        normalized =
            ((magnitude - deadzone) * 32768) / range;

        normalized = -normalized;
    }

    return clamp_i16(
        (int16_t)normalized,
        -32768,
        32767
    );
}

void es_input_init(ES_ControllerState *state)
{
    uint8_t i;

    state->button_mask = 0;

    for (i = 0; i < ES_BUTTON_COUNT; i++) {
        state->buttons[i].raw = 0;
        state->buttons[i].stable = 0;
        state->buttons[i].previous = 0;
        state->buttons[i].pressed = 0;
        state->buttons[i].released = 0;
    }

    state->lx.raw = ES_AXIS_CENTER;
    state->ly.raw = ES_AXIS_CENTER;
    state->rx.raw = ES_AXIS_CENTER;
    state->ry.raw = ES_AXIS_CENTER;

    state->lx.centered = 0;
    state->ly.centered = 0;
    state->rx.centered = 0;
    state->ry.centered = 0;

    state->lx.filtered = 0;
    state->ly.filtered = 0;
    state->rx.filtered = 0;
    state->ry.filtered = 0;

    state->lx.normalized = 0;
    state->ly.normalized = 0;
    state->rx.normalized = 0;
    state->ry.normalized = 0;

    state->lt = 0;
    state->rt = 0;
}

void es_input_update_button(
    ES_ControllerState *state,
    uint8_t index,
    uint8_t raw
)
{
    ES_ButtonState *button;

    if (index >= ES_BUTTON_COUNT)
        return;

    button = &state->buttons[index];

    button->raw = raw ? 1 : 0;

    button->previous = button->stable;
    button->stable = button->raw;

    button->pressed =
        (button->stable && !button->previous);

    button->released =
        (!button->stable && button->previous);
}

void es_input_update_axis(
    ES_AxisState *axis,
    uint16_t raw,
    int16_t deadzone
)
{
    axis->raw = raw;

    axis->centered =
        (int16_t)raw - ES_AXIS_CENTER;

    axis->filtered = axis->centered;

    axis->normalized =
        normalize_axis(axis->centered, deadzone);
}

void es_input_update_triggers(
    ES_ControllerState *state,
    uint8_t lt,
    uint8_t rt
)
{
    state->lt = lt;
    state->rt = rt;
}

void es_input_finalize(ES_ControllerState *state)
{
    uint8_t i;

    state->button_mask = 0;

    for (i = 0; i < ES_BUTTON_COUNT; i++) {
        if (state->buttons[i].stable)
            state->button_mask |= (1UL << i);
    }
}
