#include <Windows.h>
#include <Xinput.h>
#include <atomic>
#include <chrono>
#include <conio.h>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

#pragma comment(lib, "Xinput.lib")
// g++ -std=gnu++20 main.cpp -o main -lXinput

constexpr int32_t TILDA_CODE = 96;
constexpr int32_t ONE_CODE = 49;
constexpr int32_t Q_CODE = 113;
constexpr std::string FOLDER_NAME = "macros";
std::atomic<int32_t> pressed_key = -1;

enum class BUTTONS {
	A,
	B,
	X,
	Y,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	LT,
	LB,
	RT,
	RB,
	LX,
	LY,
	RX,
	RY
};

struct timed_gamepad_state {
		XINPUT_GAMEPAD state;
		std::chrono::nanoseconds timestamp;
};

constexpr std::chrono::nanoseconds FRAME_TIME =
	std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::seconds(1)) / 144;

void keyboard_listener() {
	while (true) {
		if (_kbhit()) {
			pressed_key = _getch();
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

void read_loop(std::vector<timed_gamepad_state>& states) {
	XINPUT_STATE state{};
	auto next_frame = std::chrono::steady_clock::now();
	DWORD last_packet_number = 0;
	auto last_time = std::chrono::high_resolution_clock::now();

	while (true) {
		if (XInputGetState(0, &state) == ERROR_SUCCESS) {
			if (state.dwPacketNumber != last_packet_number) {
				std::cout << state.Gamepad.sThumbLX << std::endl;
				auto now = std::chrono::high_resolution_clock::now();
				auto delta = std::chrono::duration_cast<std::chrono::nanoseconds>(now - last_time);
				states.push_back({state.Gamepad, delta});
				last_packet_number = state.dwPacketNumber;
				last_time = now;
			}
		}
		else exit(1);

		if (pressed_key == ONE_CODE) break;
		next_frame += FRAME_TIME;
		std::this_thread::sleep_until(next_frame);
	}
}

int main() {
	std::vector<timed_gamepad_state> states;

	system("cls");
	std::cout << "Macropad v0.1" << std::endl;
	std::cout << "[~] - start recording" << std::endl;
	std::cout << "[1] - stop recording" << std::endl;
	std::cout << "[q] - exit" << std::endl;
    std::cout << "[r] - read from test.bin" << std::endl;

	std::thread listener_thread(keyboard_listener);

	while (pressed_key != Q_CODE) {
		switch (pressed_key) {
			case TILDA_CODE:
				read_loop(states);

				std::string macro_name;
				std::cout << "Type macro name: ";
				std::cin >> macro_name;
				std::cout << std::endl;

				if (!std::filesystem::exists(FOLDER_NAME)) {
					std::filesystem::create_directory(FOLDER_NAME);
				}
				std::filesystem::path file_path =
					std::filesystem::path(FOLDER_NAME) / std::format("{}.bin", macro_name);
				std::ofstream out_file(file_path, std::ios::binary);
				size_t size = states.size();
				out_file.write(reinterpret_cast<const char*>(&size), sizeof(size_t));
				out_file.write(reinterpret_cast<const char*>(states.data()), size * sizeof(timed_gamepad_state));
				out_file.close();
				std::cout << "Data saved" << std::endl;
				pressed_key = Q_CODE;
		}
	}
}