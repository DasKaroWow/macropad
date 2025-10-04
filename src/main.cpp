#include "input.hpp"
#include "menu.hpp"
#include "player.hpp"
#include "recorder.hpp"
#include "structs_and_consts.hpp"
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <windows.h>
#pragma comment(lib, "Xinput.lib")
#pragma comment(lib, "setupapi.lib")
#define WIN32_LEAN_AND_MEAN
#include "ViGEmClient.h"

int main() {
	STAGES current_stage = STAGES::MAIN_MENU;
	while (true) {
		show_menu(current_stage);
		std::string filename;
		switch (current_stage) {
			case STAGES::MAIN_MENU:
				current_stage = handle_main_menu_input();
				break;
			case STAGES::RECORDING_MENU:
				current_stage = handle_recording_menu_input();
				break;
			case STAGES::PLAYING_MENU:
				current_stage = handle_playing_menu_input();
				break;
			case STAGES::RECORDING_PROCESS:
				start_recording();
				current_stage = STAGES::MAIN_MENU;
			case STAGES::QUIT_PROCESS:
				exit(0);
		}
	}
}