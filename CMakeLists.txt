cmake_minimum_required(VERSION 3.10)

project(Macropad)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(SOURCES
    src/main.cpp
    src/recorder.cpp
    src/player.cpp
    src/gamepad.cpp
    src/menu.cpp
)

add_executable(macropad ${SOURCES})

target_include_directories(macropad PUBLIC include)

if(WIN32)
    target_link_libraries(macropad PRIVATE Xinput)
endif()