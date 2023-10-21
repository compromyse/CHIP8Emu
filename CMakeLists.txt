cmake_minimum_required(VERSION 3.12)
project(chip8emu)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SDL2 REQUIRED)

include_directories(src)
file(GLOB SOURCES src/*.cpp)
add_executable(chip8emu ${SOURCES})

# Link SDL2 library
target_link_libraries(chip8emu PRIVATE SDL2::SDL2)
