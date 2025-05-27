#include "input.hpp"
#include "menu.hpp"
#include "player.hpp"
#include "recorder.hpp"
#include <cstdlib>
#include <windows.h>
#pragma comment(lib, "Xinput.lib")

int main() {
    STAGES current_stage = STAGES::MAIN_MENU;
    show_main_menu();
	while (true) {
		KEYS key = input_system::get_pressed_key();
		switch (key) {
			case KEYS::RECORD_KEY:
                if (current_stage == STAGES::MAIN_MENU) {
                    show_recording_menu();
                    current_stage = STAGES::RECORDING_MENU;
                }
                else if (current_stage == STAGES::RECORDING_MENU) {
                    Beep(1000, 100);
                    start_recording();
                    Beep(1000, 100);
                    show_main_menu();
                }
				break;
            case KEYS::EXIT_KEY:
                exit(0);
			default:
				break;
		}
	}
}