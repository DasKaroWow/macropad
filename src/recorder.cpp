#include "recorder.hpp"
#include "input.hpp"
#include "structs_and_consts.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include <thread>
#include <vector>
#include <windows.h>
#include <xinput.h>

#define XINPUT_GAMEPAD_LEFT_TRIGGER_DEADZONE 5
#define XINPUT_GAMEPAD_RIGHT_TRIGGER_DEADZONE 5
constexpr std::chrono::milliseconds FRAME_TIME =
	std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::seconds(1)) / 144;

void start_recording() {
	XINPUT_STATE state{};
	std::vector<timed_input> states;
	std::chrono::time_point next_frame = std::chrono::steady_clock::now();
	std::chrono::time_point last_time = std::chrono::steady_clock::now();
	DWORD last_packet_number = 0;
	WORD last_buttons = 0xffff;

	while (true) {
		if (XInputGetState(0, &state) == ERROR_SUCCESS) {
			if (state.dwPacketNumber != last_packet_number) {
				last_packet_number = state.dwPacketNumber;
				// Dead zones
				bool left_dead = false;
				bool right_dead = false;
				bool was_hit = state.Gamepad.wButtons ^ last_buttons != 0;
				bool was_triggers = state.Gamepad.bLeftTrigger >= XINPUT_GAMEPAD_LEFT_TRIGGER_DEADZONE or
					state.Gamepad.bRightTrigger >= XINPUT_GAMEPAD_RIGHT_TRIGGER_DEADZONE;
				if (abs(state.Gamepad.sThumbLX) < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE and
					abs(state.Gamepad.sThumbLY) < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
					left_dead = true;
				if (abs(state.Gamepad.sThumbRX) < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE and
					abs(state.Gamepad.sThumbRY) < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
					right_dead = true;
				if (left_dead and right_dead and !was_hit and !was_triggers) continue;
				// ---------
				std::chrono::time_point now = std::chrono::steady_clock::now();
				std::chrono::milliseconds delta =
					std::chrono::duration_cast<std::chrono::milliseconds>(now - last_time);
				states.push_back({state.Gamepad, delta});
				std::cout << std::format("Change state. {} since last change", delta) << std::endl;
				last_time = now;
				last_buttons = state.Gamepad.wButtons;
			}
		}
		else throw "Error while reading gamepad input";

		next_frame += FRAME_TIME;
		std::this_thread::sleep_until(next_frame);

		if (input_system::get_pressed_key() == KEYS::RECORD_KEY) {
			Beep(1'000, 100);
			save_to_file(states);
			break;
		}
	}
}

void save_to_file(const std::vector<timed_input>& data) {
	std::cout << "Enter macro name: ";
	std::string filename;
	std::cin >> filename;
	std::cout << std::endl;

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

	fs::path file_path = fs::path(FOLDER_NAME) / std::format("{}.bin", filename);
	std::ofstream out_file(file_path, std::ios::binary);
	if (!out_file) {
		std::cerr << "Error while opening file" << std::endl;
		exit(1);
	}

	try {
		size_t size = data.size();
		out_file.write(reinterpret_cast<const char*>(&size), sizeof(size_t));
		out_file.write(reinterpret_cast<const char*>(data.data()), size * sizeof(timed_input));

		if (!out_file.good()) {
			throw std::runtime_error("Error while writing");
		}
	} catch (const std::exception& e) {
		std::cerr << "Error while writing: " << e.what() << std::endl;
		out_file.close();
		exit(1);
	}

	out_file.close();
	std::cout << "Macro saved in: " << file_path << std::endl;
}