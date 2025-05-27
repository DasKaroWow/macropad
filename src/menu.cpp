#include "menu.hpp"
#include "input.hpp"
#include <iostream>
#include <string>

void show_main_menu() {
	system("cls");
	std::cout << "Macropad v0.1" << std::endl;
	std::cout << "[~] - recording menu" << std::endl;
	std::cout << "[r] - reading menu" << std::endl;
	std::cout << "[q] - exit" << std::endl;
}

void show_recording_menu() {
	system("cls");
	std::cout << "Recording menu" << std::endl;
	std::cout << "Press [~] to start record. Press [~] again to stop it and type name of macro. It will be saved in "
				 "macros folder"
			  << std::endl;
}

void display_macros() {
    system("cls");
}