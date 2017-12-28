cmake_minimum_required(VERSION 3.9)
project(Chip-8-Disassembler)

set(TOOLS_SOURCE_DIRECTORY
  "${CMAKE_CURRENT_SOURCE_DIR}/disassembler")

include_directories(${TOOLS_SOURCE_DIRECTORY}/../../includes)

set(SOURCE_HEADER_FILES
  "${TOOLS_SOURCE_DIRECTORY}/../../includes/cpu.h"
  "${TOOLS_SOURCE_DIRECTORY}/c8_disassembler.h")

set(TOOLS_SOURCES
  "${TOOLS_SOURCE_DIRECTORY}/c8_disassembler.cpp"
  "${TOOLS_SOURCE_DIRECTORY}/instructions.cpp"
  "${TOOLS_SOURCE_DIRECTORY}/main.cpp")

add_executable(c8-disassembler ${TOOLS_SOURCES} ${SOURCE_HEADER_FILES})


