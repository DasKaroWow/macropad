#pragma once
#include <Xinput.h>

struct GamepadState {
    XINPUT_STATE xstate;
    bool is_connected;
};

GamepadState getCurrentState();
void vibrate(int controller, float power);