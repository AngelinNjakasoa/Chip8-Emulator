#include "c8_disassembler.h"

std::string CPUC8Disassembler::ISIChip8Decoder::INST_00E0(uint16_t opcode) {
  return mnemonic_table[opcode];
}

std::string CPUC8Disassembler::ISIChip8Decoder::INST_00EE(uint16_t opcode) {
  return mnemonic_table[opcode];
}

std::string CPUC8Disassembler::ISIChip8Decoder::INST_1NNN(uint16_t opcode) {
  return FormatUnaryOp(mnemonic_table[OP_1NNN], GetAddr(opcode));
}

std::string CPUC8Disassembler::ISIChip8Decoder::INST_2NNN(uint16_t opcode) {
  return FormatUnaryOp(mnemonic_table[OP_2NNN], GetAddr(opcode));
}

std::string CPUC8Disassembler::ISIChip8Decoder::INST_3xkk(uint16_t opcode) {
  auto operands = GetRegisterImmediate(opcode);
  return FormatBinaryOp(mnemonic_table[OP_3XKK], "V" + operands.first, operands.second);
}

std::string CPUC8Disassembler::ISIChip8Decoder::INST_4xkk(uint16_t opcode) {
  auto operands = GetRegisterImmediate(opcode);
  return FormatBinaryOp(mnemonic_table[OP_4XKK], "V" + operands.first, operands.second);
}

std::string CPUC8Disassembler::ISIChip8Decoder::INST_5xy0(uint16_t opcode) {
  auto operands = GetRegisters(opcode);
  return FormatBinaryOp(mnemonic_table[OP_5XY0], "V" + operands.first, "V" + operands.second);
}

std::string CPUC8Disassembler::ISIChip8Decoder::INST_6xkk(uint16_t opcode) {
  auto operands = GetRegisterImmediate(opcode);
  return FormatBinaryOp(mnemonic_table[OP_6XKK], "V" + operands.first, operands.second);
}

std::string CPUC8Disassembler::ISIChip8Decoder::INST_7xkk(uint16_t opcode) {
  auto operands = GetRegisterImmediate(opcode);
  return FormatBinaryOp(mnemonic_table[OP_7XKK], "V" + operands.first, operands.second);
}

std::string CPUC8Disassembler::ISIChip8Decoder::INST_8xy0(uint16_t opcode) {
  auto operands = GetRegisters(opcode);
  return FormatBinaryOp(mnemonic_table[OP_8XY | 0x0000], "V" + operands.first, "V" + operands.second);
}

std::string CPUC8Disassembler::ISIChip8Decoder::INST_8xy1(uint16_t opcode) {
  auto operands = GetRegisters(opcode);
  return FormatBinaryOp(mnemonic_table[OP_8XY | 0x0001], "V" + operands.first, "V" + operands.second);
}

std::string CPUC8Disassembler::ISIChip8Decoder::INST_8xy2(uint16_t opcode) {
  auto operands = GetRegisters(opcode);
  return FormatBinaryOp(mnemonic_table[OP_8XY | 0x0002], "V" + operands.first, "V" + operands.second);
}

std::string CPUC8Disassembler::ISIChip8Decoder::INST_8xy3(uint16_t opcode) {
  auto operands = GetRegisters(opcode);
  return FormatBinaryOp(mnemonic_table[OP_8XY | 0x0003], "V" + operands.first, "V" + operands.second);
}

std::string CPUC8Disassembler::ISIChip8Decoder::INST_8xy4(uint16_t opcode) {
  auto operands = GetRegisters(opcode);
  return FormatBinaryOp(mnemonic_table[OP_8XY | 0x0004], "V" + operands.first, "V" + operands.second);
}

std::string CPUC8Disassembler::ISIChip8Decoder::INST_8xy5(uint16_t opcode) {
  auto operands = GetRegisters(opcode);
  return FormatBinaryOp(mnemonic_table[OP_8XY | 0x0005], "V" + operands.first, "V" + operands.second);
}

std::string CPUC8Disassembler::ISIChip8Decoder::INST_8xy6(uint16_t opcode) {
  auto operands = GetRegisters(opcode);
  return FormatBinaryOp(mnemonic_table[OP_8XY | 0x0006], "V" + operands.first, "V" + operands.second);
}

std::string CPUC8Disassembler::ISIChip8Decoder::INST_8xy7(uint16_t opcode) {
  auto operands = GetRegisters(opcode);
  return FormatBinaryOp(mnemonic_table[OP_8XY | 0x0007], "V" + operands.first, "V" + operands.second);
}

std::string CPUC8Disassembler::ISIChip8Decoder::INST_8xyE(uint16_t opcode) {
  auto operands = GetRegisters(opcode);
  return FormatBinaryOp(mnemonic_table[OP_8XY | 0x000E], "V" + operands.first, "V" + operands.second);
}

std::string CPUC8Disassembler::ISIChip8Decoder::INST_9xy0(uint16_t opcode) {
  auto operands = GetRegisters(opcode);
  return FormatBinaryOp(mnemonic_table[OP_9XY], "V" + operands.first, "V" + operands.second);
}

std::string CPUC8Disassembler::ISIChip8Decoder::INST_ANNN(uint16_t opcode) {
  std::string operand = GetAddr(opcode);
  return FormatBinaryOp(mnemonic_table[OP_ANNN], "I", operand);
}

std::string CPUC8Disassembler::ISIChip8Decoder::INST_BNNN(uint16_t opcode) {
  std::string operand = GetAddr(opcode);
  return FormatBinaryOp(mnemonic_table[OP_BNNN], operand, "V0");
}

std::string CPUC8Disassembler::ISIChip8Decoder::INST_Cxkk(uint16_t opcode) {
  auto operands = GetRegisterImmediate(opcode);
  return FormatBinaryOp(mnemonic_table[OP_CXKK], "V" + operands.first, "RANDOM_BYTE & " + operands.second);
}

std::string CPUC8Disassembler::ISIChip8Decoder::INST_Dxyn(uint16_t opcode) {
  auto operands = GetRegisters(opcode);
  return FormatBinaryOp(mnemonic_table[OP_DXYN], "V" + operands.first, "V" + operands.second);
}

std::string CPUC8Disassembler::ISIChip8Decoder::INST_Ex9E(uint16_t opcode) {
  std::string operand = GetRegister(opcode);
  return FormatUnaryOp(mnemonic_table[OP_EX | 0x009E], "V" + operand);
}

std::string CPUC8Disassembler::ISIChip8Decoder::INST_ExA1(uint16_t opcode) {
  std::string operand = GetRegister(opcode);
  return FormatUnaryOp(mnemonic_table[OP_EX | 0x00A1], "V" + operand);
}

std::string CPUC8Disassembler::ISIChip8Decoder::INST_Fx07(uint16_t opcode) {
  std::string operand = GetRegister(opcode);
  return FormatBinaryOp(mnemonic_table[OP_EX | 0x0007], "V" + operand, "DT");
}

std::string CPUC8Disassembler::ISIChip8Decoder::INST_Fx0A(uint16_t opcode) {
  std::string operand = GetRegister(opcode);
  return FormatBinaryOp(mnemonic_table[OP_EX | 0x000A], "V" + operand, "K");
}

std::string CPUC8Disassembler::ISIChip8Decoder::INST_Fx15(uint16_t opcode) {
  std::string operand = GetRegister(opcode);
  return FormatBinaryOp(mnemonic_table[OP_EX | 0x0015], "DT", "V" + operand);
}

std::string CPUC8Disassembler::ISIChip8Decoder::INST_Fx18(uint16_t opcode) {
  std::string operand = GetRegister(opcode);
  return FormatBinaryOp(mnemonic_table[OP_EX | 0x0018], "ST", "V" + operand);
}

std::string CPUC8Disassembler::ISIChip8Decoder::INST_Fx1E(uint16_t opcode) {
  std::string operand = GetRegister(opcode);
  return FormatBinaryOp(mnemonic_table[OP_EX | 0x001E], "I", "V" + operand);
}

std::string CPUC8Disassembler::ISIChip8Decoder::INST_Fx29(uint16_t opcode) {
  std::string operand = GetRegister(opcode);
  return FormatBinaryOp(mnemonic_table[OP_EX | 0x0029], "F", "V" + operand);
}

std::string CPUC8Disassembler::ISIChip8Decoder::INST_Fx33(uint16_t opcode) {
  std::string operand = GetRegister(opcode);
  return FormatBinaryOp(mnemonic_table[OP_EX | 0x0033], "B", "V" + operand);
}

std::string CPUC8Disassembler::ISIChip8Decoder::INST_Fx55(uint16_t opcode) {
  std::string operand = GetRegister(opcode);
  return FormatBinaryOp(mnemonic_table[OP_EX | 0x0055], "[I]", "V" + operand);
}

std::string CPUC8Disassembler::ISIChip8Decoder::INST_Fx65(uint16_t opcode) {
  std::string operand = GetRegister(opcode);
  return FormatBinaryOp(mnemonic_table[OP_EX | 0x0065], "V" + operand, "[I]");
}
