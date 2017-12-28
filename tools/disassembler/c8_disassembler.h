#ifndef __DISASSEMBLER_H__
# define __DISASSEMBLER_H__

#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <utility>
#include "cpu.h"
#include "loader.h"

/* Loads a ROM to memory and disassemble each opcode */
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

  /* Load the ROM in memory */
  void LoadBinary(const char* path);

  /* Disassemble the ROM loaded in memory */
  void Disassemble();

  /* Fetch the next opcode and disassemble it */
  bool DisassembleOpcode();

  /* Fetch the next opcode from byte stream */
  uint16_t GetOpcodeFromByteStream();

  /* Returns the size of loaded ROM */
  /* size: number of byte */
  int GetBufferSize();

  /* Returns the current offset */
  uint16_t GetOffset();

  /* Increase the offset value */
  uint16_t MoveOffsetForward(const uint16_t incr_value);

  /* Decrease the offset value */
  uint16_t MoveOffsetBackward(const uint16_t decr_value);

  /* Sets the offset to 0 */
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

    /* Initialize the mnemonic_table */
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

    /* Returns the NNN address for 1NNN, 2NNN, ANNN and BNNN instructions */
    std::string GetAddr(uint16_t opcode) {
      ClearStream();
      sstream << std::hex << static_cast<int>(opcode & 0x0FFF);
      return sstream.str();
    }

    /* Returns a std::pair<string, string> */
    /* first: contains a register number */
    /* second: contains an immediate value */
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

    /* Returns a st::pair<string, string> */
    /* first: contains a register number */
    /* second: contains a register number */
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

    /* Return a register number */
    std::string GetRegister(uint16_t opcode) {
      ClearStream();
      sstream << std::hex << static_cast<int>((opcode & 0x0F00) >> 8);
      return sstream.str();
    }

    std::string FormatBinaryOp(std::string mnemonic, std::string op1, std::string op2) {
      /* TODO(Lemme): implement a solution to write the disassembled opcode to a fd or stream */
      std::cout << mnemonic + " " + op1 + ", " + op2 << std::endl;
      return mnemonic + " " + op1 + ", " + op2;
    }

    std::string FormatUnaryOp(std::string mnemonic, std::string operand) {
      /* TODO(Lemme): implement a solution to write the disassembled opcode to a fd or stream */
      std::cout << mnemonic + " " + operand << std::endl;
      return mnemonic + " " + operand;
    }

    /* Implements of the opcode decoder for each encoded instruction */
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
