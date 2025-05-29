#pragma once
#include "structs_and_consts.hpp"
#include <string>
#include <vector>
#include <xinput.h>

std::vector<timed_input> load_macro(const std::string& filename);
void play_macro(const std::vector<timed_input>& states);
