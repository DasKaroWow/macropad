#pragma once
#include <conio.h>
#include <cstdint>

enum KEYS : int32_t {
	RECORD_KEY = 96,
	EXIT_KEY = 113,
	UNKNOWN = -1
};

class input_system {
	public:
		static KEYS get_pressed_key() {
			if (_kbhit()) {
				switch (_getch()) {
					case KEYS::RECORD_KEY:
						return KEYS::RECORD_KEY;
					case KEYS::EXIT_KEY:
						return KEYS::EXIT_KEY;
				}
			}
			return KEYS::UNKNOWN;
		}
};