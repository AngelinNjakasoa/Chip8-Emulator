#include "c8_disassembler.h"

void CPUC8Disassembler::LoadBinary(const char* path) {
  std::cout << path << std::endl;
}

void CPUC8Disassembler::Disassemble() {
  std::cout << "Disassemble" << std::endl;
}

int CPUC8Disassembler::GetBufferSize() {
  return loader.GetBufferSize();
}

uint16_t CPUC8Disassembler::GetCurrentOffset() {
  return current_offset;
}

uint16_t CPUC8Disassembler::MoveOffsetForward(const uint16_t incr_value) {
  current_offset += incr_value;
  return current_offset;
}

uint16_t CPUC8Disassembler::MoveOffsetBackward(const uint16_t decr_value) {
  current_offset -= decr_value;
  return current_offset;
}

uint16_t CPUC8Disassembler::ResetOffset() {
  current_offset = 0;
  return current_offset;
}

void CPUC8Disassembler::DisassembleOpcode(uint16_t opcode) {
  std::cout << "Disassemble opcode: " << std::hex << opcode << std::endl;
}
