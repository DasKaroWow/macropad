#include "menu.hpp"
#include "input.hpp"
#include "structs_and_consts.hpp"
#include <filesystem>
#include <format>
#include <iostream>
#include <string>

std::vector<std::string> get_macros() {
	if (!fs::exists(FOLDER_NAME)) {
		try {
			if (!fs::create_directory(FOLDER_NAME)) {
				std::cerr << "Error while creating folder " << FOLDER_NAME << std::endl;
				exit(1);
			}
		} catch (const fs::filesystem_error& e) {
			std::cerr << "Filesystem error: " << e.what() << std::endl;
			exit(1);
		}
	}

	fs::path path = fs::path(FOLDER_NAME);
	std::vector<std::string> macros;
	for (const auto& f : fs::directory_iterator(path)) macros.push_back(f.path().string());
    return macros;
}

void show_menu(STAGES current_stage) {
	system("cls");
	switch (current_stage) {
		case STAGES::MAIN_MENU:
			std::cout << "Macropad v0.1" << std::endl;
			std::cout << "[~] - recording menu" << std::endl;
			std::cout << "[p] - reading menu" << std::endl;
			std::cout << "[q] - exit" << std::endl;
			break;
		case STAGES::RECORDING_MENU:
			std::cout << "Recording menu" << std::endl;
			std::cout
				<< "Press [~] to start record. Press [~] again to stop it and type name of macro. It will be saved in "
				   "macros folder"
				<< std::endl;
			break;
		case STAGES::PLAYING_MENU:
			std::cout << "Macros:" << std::endl;
			std::vector<std::string> macros = std::move(get_macros());
			for (size_t i = 1; i <= macros.size(); ++i)
				std::cout << std::format("[{}] - {}", i, macros[i - 1]) << std::endl;
			break;
	}
}

STAGES handle_main_menu_input() {
	while (true) {
		KEYS key = input_system::get_pressed_key();
		switch (key) {
			case KEYS::RECORD_KEY:
				return STAGES::RECORDING_MENU;
			case KEYS::PLAY_KEY:
				return STAGES::PLAYING_MENU;
			case KEYS::EXIT_KEY:
				return STAGES::QUIT_PROCESS;
		}
	}
}

STAGES handle_recording_menu_input() {
	while (true) {
		KEYS key = input_system::get_pressed_key();
		switch (key) {
			case KEYS::RECORD_KEY:
				return STAGES::RECORDING_PROCESS;
			case KEYS::EXIT_KEY:
				return STAGES::MAIN_MENU;
		}
	}
}

STAGES handle_playing_menu_input() {
	return STAGES::QUIT_PROCESS;
}