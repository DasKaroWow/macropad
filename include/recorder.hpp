#pragma once
#include "gamepad.hpp"
#include <chrono>
#include <string>
#include <vector>
#include <xinput.h>

constexpr std::chrono::milliseconds FRAME_TIME =
	std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::seconds(1)) / 144;

struct timed_input;

void start_recording();
void save_to_file(const std::vector<timed_input>& data);