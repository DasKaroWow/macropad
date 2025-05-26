#include <Windows.h>
#include <chrono>
#include <conio.h>
#include <iostream>
#include <thread>
#include <unordered_map>
#pragma comment(lib, "Xinput.lib")
// g++ main.cpp -o main -lXinput

int main() {
    while (true) {
        std::cout << _kbhit() << std::endl;
	if (_kbhit()) {
		int key = _getch();
		std::cout << key << std::endl;
	}
}
}