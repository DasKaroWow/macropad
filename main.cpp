#include <Windows.h>
#include <Xinput.h>
#pragma comment(lib, "Xinput.lib")
// g++ main.cpp -o main -lXinput

int main() {
    XINPUT_STATE state;
    ZeroMemory(&state, sizeof(XINPUT_STATE));

    while (true) {
        if (XInputGetState(0, &state) == ERROR_SUCCESS) {
            WORD buttons = state.Gamepad.wButtons;
            bool a_button = (buttons & XINPUT_GAMEPAD_A) != 0;
            float left_trigger = state.Gamepad.bLeftTrigger / 255.0f;
            // Аналогично для других кнопок и осей
        }
    }
}