cmake_minimum_required(VERSION 3.9)
project(Chip-8-Disassembler)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

set(TOOLS_SOURCE_DIRECTORY
  "${CMAKE_CURRENT_SOURCE_DIR}/sources")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/includes)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../includes)

set(SOURCE_HEADER_FILES
  "${CMAKE_CURRENT_SOURCE_DIR}/../../includes/cpu.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/includes/c8_disassembler.h")

set(TOOLS_SOURCES
  "${TOOLS_SOURCE_DIRECTORY}/c8_disassembler.cpp"
  "${TOOLS_SOURCE_DIRECTORY}/instructions.cpp"
  "${TOOLS_SOURCE_DIRECTORY}/main.cpp")

add_executable(c8-disassembler ${TOOLS_SOURCES} ${SOURCE_HEADER_FILES})
