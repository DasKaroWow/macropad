cmake_minimum_required(VERSION 3.10)
project(ViGEmClient)

add_library(ViGEmClient SHARED src/ViGEmClient.cpp)
target_include_directories(ViGEmClient PRIVATE include)
target_link_libraries(ViGEmClient setupapi hid)