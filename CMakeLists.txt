cmake_minimum_required(VERSION 3.10)
project(macropad)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
set(LIB_DIR "${PROJECT_SOURCE_DIR}/lib")
set(DLL_DIR "${PROJECT_SOURCE_DIR}/bin")
set(SOURCES
    src/main.cpp
    src/recorder.cpp
    src/player.cpp
    src/menu.cpp
)

include_directories(${INCLUDE_DIR})
add_executable(macropad ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${LIB_DIR}/ViGEmClient.dll.a)
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} Xinput)

if(WIN32)
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            "${DLL_DIR}/ViGEmClient.dll"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
        COMMENT "Копирование ViGEmClient.dll"
    )
endif()