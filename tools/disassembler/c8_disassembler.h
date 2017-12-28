#ifndef __DISASSEMBLER_H__
# define __DISASSEMBLER_H__

#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <utility>
#include "cpu.h"
#include "loader.h"

class CPUC8Disassembler {
 public:
 CPUC8Disassembler()
   : byte_stream(nullptr), buffer_size(0), offset(0) {}

  ~CPUC8Disassembler() {
    if (byte_stream != nullptr) {
      delete [] byte_stream;
      byte_stream = nullptr;
    }
  }

  void LoadBinary(const char* path);
  void Disassemble();
  bool DisassembleOpcode();
  uint16_t GetOpcodeFromByteStream();
  int GetBufferSize();
  uint16_t GetOffset();
  uint16_t MoveOffsetForward(const uint16_t incr_value);
  uint16_t MoveOffsetBackward(const uint16_t decr_value);
  uint16_t ResetOffset();

 private:
  /* Instruction set opcode decoder */
  class ISIChip8Decoder {
  public:

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

  ISIChip8Decoder() {
      mnemonic_table[0x00E0] = "CLS";
      mnemonic_table[0x00EE] = "RET";
      mnemonic_table[OP_1NNN] = "JP";
      mnemonic_table[OP_2NNN] = "CALL";
      mnemonic_table[OP_3XKK] = "SE";
      mnemonic_table[OP_4XKK] = "SNE";
      mnemonic_table[OP_5XY0] = "SE";
      mnemonic_table[OP_6XKK] = "LD";
      mnemonic_table[OP_7XKK] = "ADD";
      mnemonic_table[OP_8XY | 0x0000] = "LD";
      mnemonic_table[OP_8XY | 0x0001] = "OR";
      mnemonic_table[OP_8XY | 0x0002] = "AND";
      mnemonic_table[OP_8XY | 0x0003] = "XOR";
      mnemonic_table[OP_8XY | 0x0004] = "ADD";
      mnemonic_table[OP_8XY | 0x0005] = "SUB";
      mnemonic_table[OP_8XY | 0x0006] = "SHR";
      mnemonic_table[OP_8XY | 0x0007] = "SUBN";
      mnemonic_table[OP_8XY | 0x000E] = "SHL";
      mnemonic_table[OP_9XY] = "SNE";
      mnemonic_table[OP_ANNN] = "LD";
      mnemonic_table[OP_BNNN] = "JP";
      mnemonic_table[OP_CXKK] = "RND";
      mnemonic_table[OP_DXYN] = "DRW";
      mnemonic_table[OP_EX | 0x009E] = "SKP";
      mnemonic_table[OP_EX | 0x00A1] = "SKNP";
      mnemonic_table[OP_FX] = "LD";
      mnemonic_table[OP_FX | 0x001E] = "ADD";
    }

    void ClearStream() {
      sstream.str("");
    }

    /* Get the NNN address for 1NNN, 2NNN, ANNN and BNNN instructions */
    std::string GetAddr(uint16_t opcode) {
      ClearStream();
      sstream << std::hex << static_cast<int>(opcode & 0x0FFF);
      return sstream.str();
    }

    std::pair<std::string, std::string> GetRegisterImmediate(uint16_t opcode) {
      ClearStream();
      std::pair<std::string, std::string> operands;
      sstream << std::hex << static_cast<int>((opcode & 0x0F00) >> 8);
      operands.first = sstream.str();
      ClearStream();
      sstream << std::hex << static_cast<int>(opcode & 0x00FF);
      operands.second = sstream.str();
      return operands;
    }

    std::pair<std::string, std::string> GetRegisters(uint16_t opcode) {
      ClearStream();
      std::pair<std::string, std::string> operands;
      sstream << std::hex << static_cast<int>((opcode & 0x0F00) >> 8);
      operands.first = sstream.str();
      ClearStream();
      sstream << std::hex << static_cast<int>((opcode & 0x00F0) >> 4);
      operands.second = sstream.str();
      return operands;
    }

    std::string GetRegister(uint16_t opcode) {
      ClearStream();
      sstream << std::hex << static_cast<int>((opcode & 0x0F00) >> 8);
      return sstream.str();
    }

    std::string FormatBinaryOp(std::string mnemonic, std::string op1, std::string op2) {
      std::cout << mnemonic + " " + op1 + ", " + op2 << std::endl;
      return mnemonic + " " + op1 + ", " + op2;
    }

    std::string FormatUnaryOp(std::string mnemonic, std::string operand) {
      std::cout << mnemonic + " " + operand << std::endl;
      return mnemonic + " " + operand;
    }

    /* Implementation of the opcode decoder */
    std::string INST_00E0(uint16_t opcode);
    std::string INST_00EE(uint16_t opcode);
    std::string INST_1NNN(uint16_t opcode);
    std::string INST_2NNN(uint16_t opcode);
    std::string INST_3xkk(uint16_t opcode);
    std::string INST_4xkk(uint16_t opcode);
    std::string INST_5xy0(uint16_t opcode);
    std::string INST_6xkk(uint16_t opcode);
    std::string INST_7xkk(uint16_t opcode);
    std::string INST_8xy0(uint16_t opcode);
    std::string INST_8xy1(uint16_t opcode);
    std::string INST_8xy2(uint16_t opcode);
    std::string INST_8xy3(uint16_t opcode);
    std::string INST_8xy4(uint16_t opcode);
    std::string INST_8xy5(uint16_t opcode);
    std::string INST_8xy6(uint16_t opcode);
    std::string INST_8xy7(uint16_t opcode);
    std::string INST_8xyE(uint16_t opcode);
    std::string INST_9xy0(uint16_t opcode);
    std::string INST_ANNN(uint16_t opcode);
    std::string INST_BNNN(uint16_t opcode);
    std::string INST_Cxkk(uint16_t opcode);
    std::string INST_Dxyn(uint16_t opcode);
    std::string INST_Ex9E(uint16_t opcode);
    std::string INST_ExA1(uint16_t opcode);
    std::string INST_Fx07(uint16_t opcode);
    std::string INST_Fx0A(uint16_t opcode);
    std::string INST_Fx15(uint16_t opcode);
    std::string INST_Fx18(uint16_t opcode);
    std::string INST_Fx1E(uint16_t opcode);
    std::string INST_Fx29(uint16_t opcode);
    std::string INST_Fx33(uint16_t opcode);
    std::string INST_Fx55(uint16_t opcode);
    std::string INST_Fx65(uint16_t opcode);

  private:
    std::stringstream sstream;
    std::map<uint16_t, std::string> mnemonic_table;
  };

  LoaderC8 loader;
  uint8_t *byte_stream;
  int buffer_size;
  uint16_t offset;
  ISIChip8Decoder isi_decoder;
};

#endif /* DISASSEMBLER_H */
