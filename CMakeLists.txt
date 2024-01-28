cmake_minimum_required(VERSION 3.12)
project(chip8emu)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "-sUSE_SDL=2 -pthread -sPTHREAD_POOL_SIZE=3 --embed-file ../roms@roms")

include_directories(src)
file(GLOB SOURCES src/*.cpp)
add_executable(chip8emu ${SOURCES})

# Link SDL2 library
target_link_libraries(chip8emu PRIVATE ${SDL2_LIBRARIES})
set(CMAKE_EXECUTABLE_SUFFIX ".html")
