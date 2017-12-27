#ifndef __DISASSEMBLER_H__
# define __DISASSEMBLER_H__

#include <iostream>
#include <string>
#include "cpu.h"
#include "loader.h"

class CPUC8Disassembler {
 public:
  void LoadBinary(const char* path) {
    std::cout << path << std::endl;
  }

  void Disassemble() {
    std::cout << "Disassemble" << std::endl;
  }

  int GetBufferSize() {
    return loader.GetBufferSize();
  }

  uint16_t GetCurrentOffset() {
    return current_offset;
  }

  uint16_t MoveOffsetForward(const uint16_t incr_value) {
    current_offset += incr_value;
    return current_offset;
  }

  uint16_t MoveOffsetBackward(const uint16_t decr_value) {
    current_offset -+ decr_value;
    return current_offset;
  }

  uint16_t ResetOffset() {
    current_offset = 0;
    return current_offset;
  }

  void DisassembleOpcode(uint16_t opcode) {
    std::cout << "Disassemble opcode: " << std::hex << opcode << std::endl;
  }

 private:
  /* Instruction set opcode decoder */
  class ISIChip8Decoder {
  public:
  ISIChip8Decoder(CPUChip8 &outer) : cpu(outer) {}
    enum OPCODE {
      OP_0NNN = 0x0000,
      OP_1NNN = 0x1000,
      OP_2NNN = 0x2000,
      OP_3XKK = 0x3000,
      OP_4XKK = 0x4000,
      OP_5XY0 = 0x5000,
      OP_6XKK = 0x6000,
      OP_7XKK = 0x7000,
      OP_8XY = 0x8000,
      OP_9XY = 0x9000,
      OP_ANNN = 0xA000,
      OP_BNNN = 0xB000,
      OP_CXKK = 0xC000,
      OP_DXYN = 0xD000,
      OP_EX = 0xE000,
      OP_FX = 0xF000,
    };

    /* Implementation of the opcode decoder */
    void INST_00E0(uint16_t opcode);
    void INST_00EE(uint16_t opcode);
    void INST_1NNN(uint16_t opcode);
    void INST_2NNN(uint16_t opcode);
    void INST_3xkk(uint16_t opcode);
    void INST_4xkk(uint16_t opcode);
    void INST_5xy0(uint16_t opcode);
    void INST_6xkk(uint16_t opcode);
    void INST_7xkk(uint16_t opcode);
    void INST_8xy0(uint16_t opcode);
    void INST_8xy1(uint16_t opcode);
    void INST_8xy2(uint16_t opcode);
    void INST_8xy3(uint16_t opcode);
    void INST_8xy4(uint16_t opcode);
    void INST_8xy5(uint16_t opcode);
    void INST_8xy6(uint16_t opcode);
    void INST_8xy7(uint16_t opcode);
    void INST_8xyE(uint16_t opcode);
    void INST_9xy0(uint16_t opcode);
    void INST_ANNN(uint16_t opcode);
    void INST_BNNN(uint16_t opcode);
    void INST_Cxkk(uint16_t opcode);
    void INST_Dxyn(uint16_t opcode);
    void INST_Ex9E(uint16_t opcode);
    void INST_ExA1(uint16_t opcode);
    void INST_Fx07(uint16_t opcode);
    void INST_Fx0A(uint16_t opcode);
    void INST_Fx15(uint16_t opcode);
    void INST_Fx18(uint16_t opcode);
    void INST_Fx1E(uint16_t opcode);
    void INST_Fx29(uint16_t opcode);
    void INST_Fx33(uint16_t opcode);
    void INST_Fx55(uint16_t opcode);
    void INST_Fx65(uint16_t opcode);

  private:
    CPUChip8& cpu;
  };

  LoaderC8 loader;
  uint16_t current_offset;
  uint16_t max_offset;
};

#endif /* DISASSEMBLER_H */
