#ifndef ELECTRIC_SHOCK_CONTROLLER_H
#define ELECTRIC_SHOCK_CONTROLLER_H

#include <stdint.h>

typedef struct {
    uint16_t x;
    uint16_t y;
} JoystickAxis;

typedef struct {
    uint32_t buttons;

    JoystickAxis left;
    JoystickAxis right;

    uint8_t triggers[2];
} ControllerState;

void controller_init(void);
void controller_sample(ControllerState *state);

#endif
