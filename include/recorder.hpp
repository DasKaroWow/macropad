#pragma once
#include <chrono>
#include <string>
#include <vector>
#include <xinput.h>
#include "structs_and_consts.hpp"

constexpr std::chrono::milliseconds FRAME_TIME =
	std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::seconds(1)) / 144;


void start_recording();
void save_to_file(const std::vector<timed_input>& data);