#include "player.hpp"
#include "structs_and_consts.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <xinput.h>
#include "ViGEmClient.h"

std::vector<timed_input> load_macro(const std::string& filename) {
	fs::path path = fs::path(FOLDER_NAME) / filename;
	if (!fs::exists(path)) return {};

	std::ifstream in_file(path, std::ios::binary);
	size_t size;
	in_file.read(reinterpret_cast<char*>(&size), sizeof(size_t));
	std::vector<timed_input> states(size);
	in_file.read(reinterpret_cast<char*>(states.data()), size * sizeof(timed_input));
	return states;
}
void play_macro(const std::vector<timed_input>& states) {
    
}
