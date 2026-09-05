#include <stdio.h>
#include <assert.h>

#include "input.h"

static void test_axis_center(void)
{
    ES_AxisState axis;

    es_input_update_axis(
        &axis,
        ES_AXIS_CENTER,
        ES_DEFAULT_DEADZONE
    );

    assert(axis.centered == 0);
    assert(axis.normalized == 0);
}

static void test_axis_positive(void)
{
    ES_AxisState axis;

    es_input_update_axis(
        &axis,
        ES_AXIS_MAX,
        ES_DEFAULT_DEADZONE
    );

    assert(axis.normalized > 30000);
}

static void test_axis_negative(void)
{
    ES_AxisState axis;

    es_input_update_axis(
        &axis,
        ES_AXIS_MIN,
        ES_DEFAULT_DEADZONE
    );

    assert(axis.normalized < -30000);
}

static void test_button_edges(void)
{
    ES_ControllerState state;

    es_input_init(&state);

    es_input_update_button(&state, 0, 0);
    assert(state.buttons[0].pressed == 0);

    es_input_update_button(&state, 0, 1);
    assert(state.buttons[0].pressed == 1);

    es_input_update_button(&state, 0, 1);
    assert(state.buttons[0].pressed == 0);

    es_input_update_button(&state, 0, 0);
    assert(state.buttons[0].released == 1);
}

static void test_button_mask(void)
{
    ES_ControllerState state;

    es_input_init(&state);

    es_input_update_button(&state, 0, 1);
    es_input_update_button(&state, 3, 1);
    es_input_update_button(&state, 7, 1);

    es_input_finalize(&state);

    assert(state.button_mask & (1UL << 0));
    assert(state.button_mask & (1UL << 3));
    assert(state.button_mask & (1UL << 7));

    assert(!(state.button_mask & (1UL << 1)));
}

int main(void)
{
    test_axis_center();
    test_axis_positive();
    test_axis_negative();
    test_button_edges();
    test_button_mask();

    printf("input tests: PASS\n");

    return 0;
}
