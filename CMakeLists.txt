cmake_minimum_required (VERSION 3.9)
project(Chip-8)

find_package(SDL2 REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

set(SOURCE_DIRECTORY
  "${CMAKE_CURRENT_SOURCE_DIR}")

include_directories(${SOURCE_DIRECTORY}/includes ${SDL2_INCLUDE_DIRS})

set(HEADER_FILES
  "${SOURCE_DIRECTORY}/includes/cpu.h"
  "${SOURCE_DIRECTORY}/includes/memory.h"
  "${SOURCE_DIRECTORY}/includes/gpu.h"
  "${SOURCE_DIRECTORY}/includes/controller.h"
  "${SOURCE_DIRECTORY}/includes/loader.h"
  "${SOURCE_DIRECTORY}/includes/chip8_emulator.h")

set(SOURCES
  "${SOURCE_DIRECTORY}/sources/cpu.cpp"
  "${SOURCE_DIRECTORY}/sources/instructions.cpp"
  "${SOURCE_DIRECTORY}/sources/main.cpp")

add_executable(chip8 ${SOURCES} ${HEADER_FILES})
target_link_libraries(chip8 ncurses ${SDL2_LIBRARIES})
