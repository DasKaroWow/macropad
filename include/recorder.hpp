#pragma once
#include <chrono>
#include <string>
#include <vector>
#include <xinput.h>
#include "structs_and_consts.hpp"

void start_recording();
void save_to_file(const std::vector<timed_input>& data);