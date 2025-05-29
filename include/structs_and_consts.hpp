#include <chrono>
#include <filesystem>
#include <string>
#include <xinput.h>
#pragma once

namespace fs = std::filesystem;
constexpr std::string FOLDER_NAME = "macros";

struct timed_input {
		XINPUT_GAMEPAD state;
		std::chrono::milliseconds time_delta;
};