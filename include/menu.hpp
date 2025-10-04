#pragma once
#include "input.hpp"
#include "menu.hpp"
#include "structs_and_consts.hpp"
#include <filesystem>
#include <format>
#include <iostream>
#include <string>

enum class STAGES {
	MAIN_MENU,
	RECORDING_MENU,
	PLAYING_MENU,
	QUIT_PROCESS,
	RECORDING_PROCESS,
    PLAYING_PROCESS,
};

std::vector<std::string> get_macros();
void show_menu(STAGES current_stage);
STAGES handle_main_menu_input();
STAGES handle_recording_menu_input();
STAGES handle_playing_menu_input();