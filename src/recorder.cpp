#include "recorder.hpp"
#include "input.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <windows.h>
#include <xinput.h>
#pragma comment(lib, "Xinput.lib")

struct timed_input {
		XINPUT_GAMEPAD state;
		std::chrono::milliseconds time_delta;
};

void start_recording() {
	XINPUT_STATE state{};
	std::vector<timed_input> states;
	std::chrono::time_point next_frame = std::chrono::steady_clock::now();
	std::chrono::time_point last_time = std::chrono::steady_clock::now();
	DWORD last_packet_number = 0;

	while (true) {
		if (XInputGetState(0, &state) == ERROR_SUCCESS) {
			if (state.dwPacketNumber != last_packet_number) {
                std::chrono::time_point now = std::chrono::steady_clock::now();
				std::chrono::milliseconds delta =
                std::chrono::duration_cast<std::chrono::milliseconds>(now - last_time);
				states.push_back({state.Gamepad, delta});
                std::cout << std::format("Change state. {} since last change", delta) << std::endl;
				last_packet_number = state.dwPacketNumber;
				last_time = now;
			}
		}
		else exit(1);

		next_frame += FRAME_TIME;
		std::this_thread::sleep_until(next_frame);

		if (input_system::get_pressed_key() == KEYS::RECORD_KEY) {
            save_to_file(states);
            break;
        }
	}
}

namespace fs = std::filesystem;
constexpr std::string FOLDER_NAME = "macros";
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