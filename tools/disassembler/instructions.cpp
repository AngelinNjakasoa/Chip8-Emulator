#include "c8_disassembler.h"

/* Opcode 0x00EE -> CLS */
std::string CPUC8Disassembler::ISIChip8Decoder::INST_00E0(uint16_t opcode) {
  return mnemonic_table[opcode];
}

/* Opcode 00EE -> RET */
std::string CPUC8Disassembler::ISIChip8Decoder::INST_00EE(uint16_t opcode) {
  return mnemonic_table[opcode];
}

/* Opcode 01nnn -> JP 0xnnn */
/* nnn: address */
std::string CPUC8Disassembler::ISIChip8Decoder::INST_1NNN(uint16_t opcode) {
  return FormatUnaryOp(mnemonic_table[OP_1NNN], "0x" + GetAddr(opcode));
}

/* Opcode 2nnn -> CALL 0xnnn */
/* nnn: address */
std::string CPUC8Disassembler::ISIChip8Decoder::INST_2NNN(uint16_t opcode) {
  return FormatUnaryOp(mnemonic_table[OP_2NNN], "0x" + GetAddr(opcode));
}

/* Opcode 3xkk -> SE Vx, 0xkk */
/* x: register number */
/* kk: byte */
std::string CPUC8Disassembler::ISIChip8Decoder::INST_3xkk(uint16_t opcode) {
  auto operands = GetRegisterImmediate(opcode);
  return FormatBinaryOp(mnemonic_table[OP_3XKK], "V" + operands.first, "0x" + operands.second);
}

/* Opcode 4xkk -> SNE Vx, 0xkk */
/* x: register number */
/* kk: byte */
std::string CPUC8Disassembler::ISIChip8Decoder::INST_4xkk(uint16_t opcode) {
  auto operands = GetRegisterImmediate(opcode);
  return FormatBinaryOp(mnemonic_table[OP_4XKK], "V" + operands.first, "0x" + operands.second);
}

/* Opcode 5xy0 -> LD Vx, Vy*/
/* x: register number */
/* y: register number */
std::string CPUC8Disassembler::ISIChip8Decoder::INST_5xy0(uint16_t opcode) {
  auto operands = GetRegisters(opcode);
  return FormatBinaryOp(mnemonic_table[OP_5XY0], "V" + operands.first, "V" + operands.second);
}

/* Opcode 6xkk -> LD Vx, 0xkk */
/* x: register number */
/* kk: byte */
std::string CPUC8Disassembler::ISIChip8Decoder::INST_6xkk(uint16_t opcode) {
  auto operands = GetRegisterImmediate(opcode);
  return FormatBinaryOp(mnemonic_table[OP_6XKK], "V" + operands.first, "0x" + operands.second);
}

/* Opcode 7xkk -> ADD Vx, 0xkk */
/* x: register number */
/* kk: byte */
std::string CPUC8Disassembler::ISIChip8Decoder::INST_7xkk(uint16_t opcode) {
  auto operands = GetRegisterImmediate(opcode);
  return FormatBinaryOp(mnemonic_table[OP_7XKK], "V" + operands.first, "0x" + operands.second);
}

/* Opcode 8xy0 -> LD Vx, Vy */
/* x: register number */
/* y: register number */
std::string CPUC8Disassembler::ISIChip8Decoder::INST_8xy0(uint16_t opcode) {
  auto operands = GetRegisters(opcode);
  return FormatBinaryOp(mnemonic_table[OP_8XY | 0x0000], "V" + operands.first, "V" + operands.second);
}

/* Opcode 8xy1 -> OR Vx, Vy */
/* x: register number */
/* y: register number */
std::string CPUC8Disassembler::ISIChip8Decoder::INST_8xy1(uint16_t opcode) {
  auto operands = GetRegisters(opcode);
  return FormatBinaryOp(mnemonic_table[OP_8XY | 0x0001], "V" + operands.first, "V" + operands.second);
}

/* Opcode 8xy2 -> AND Vx, Vy */
/* x: register number */
/* y: register number */
std::string CPUC8Disassembler::ISIChip8Decoder::INST_8xy2(uint16_t opcode) {
  auto operands = GetRegisters(opcode);
  return FormatBinaryOp(mnemonic_table[OP_8XY | 0x0002], "V" + operands.first, "V" + operands.second);
}

/* Opcode 8xy3 -> XOR Vx, Vy */
/* x: register number */
/* y: register number */
std::string CPUC8Disassembler::ISIChip8Decoder::INST_8xy3(uint16_t opcode) {
  auto operands = GetRegisters(opcode);
  return FormatBinaryOp(mnemonic_table[OP_8XY | 0x0003], "V" + operands.first, "V" + operands.second);
}

/* Opcode 8xy4 -> ADD Vx, Vy */
/* x: register number */
/* y: register number */
std::string CPUC8Disassembler::ISIChip8Decoder::INST_8xy4(uint16_t opcode) {
  auto operands = GetRegisters(opcode);
  return FormatBinaryOp(mnemonic_table[OP_8XY | 0x0004], "V" + operands.first, "V" + operands.second);
}

/* Opcode 8xy5 -> SUB Vx, Vy */
/* x: register number */
/* y: register number */
std::string CPUC8Disassembler::ISIChip8Decoder::INST_8xy5(uint16_t opcode) {
  auto operands = GetRegisters(opcode);
  return FormatBinaryOp(mnemonic_table[OP_8XY | 0x0005], "V" + operands.first, "V" + operands.second);
}

/* Opcode 8xy6 -> SHR Vx {, Vy} */
/* x: register number */
/* y: register number */
std::string CPUC8Disassembler::ISIChip8Decoder::INST_8xy6(uint16_t opcode) {
  auto operands = GetRegisters(opcode);
  return FormatBinaryOp(mnemonic_table[OP_8XY | 0x0006], "V" + operands.first, "V" + operands.second);
}

/* Opcode 8xy7 -> SUBN Vx, Vy */
/* x: register number */
/* y: register number */
std::string CPUC8Disassembler::ISIChip8Decoder::INST_8xy7(uint16_t opcode) {
  auto operands = GetRegisters(opcode);
  return FormatBinaryOp(mnemonic_table[OP_8XY | 0x0007], "V" + operands.first, "V" + operands.second);
}

/* Opcode 8xyE -> SHL Vx {, Vy} */
/* x: register number */
/* y: register number */
std::string CPUC8Disassembler::ISIChip8Decoder::INST_8xyE(uint16_t opcode) {
  auto operands = GetRegisters(opcode);
  return FormatBinaryOp(mnemonic_table[OP_8XY | 0x000E], "V" + operands.first, "V" + operands.second);
}

/* Opcode 9xy0 -> SNE Vx, Vy */
/* x: register number */
/* y: register number */
std::string CPUC8Disassembler::ISIChip8Decoder::INST_9xy0(uint16_t opcode) {
  auto operands = GetRegisters(opcode);
  return FormatBinaryOp(mnemonic_table[OP_9XY], "V" + operands.first, "V" + operands.second);
}

/* Opcode Annn -> LD I, 0xnnn */
/* nnn: address */
std::string CPUC8Disassembler::ISIChip8Decoder::INST_ANNN(uint16_t opcode) {
  std::string operand = GetAddr(opcode);
  return FormatBinaryOp(mnemonic_table[OP_ANNN], "I", "0x" + operand);
}

/* Opcode Bnnn -> JP V0, 0xnnn */
/* nnn: address */
std::string CPUC8Disassembler::ISIChip8Decoder::INST_BNNN(uint16_t opcode) {
  std::string operand = GetAddr(opcode);
  return FormatBinaryOp(mnemonic_table[OP_BNNN], "0x" + operand, "V0");
}

/* Opcode Cxkk -> RND Vx, 0xkk */
/* x: register number */
/* kk: byte */
std::string CPUC8Disassembler::ISIChip8Decoder::INST_Cxkk(uint16_t opcode) {
  auto operands = GetRegisterImmediate(opcode);
  return FormatBinaryOp(mnemonic_table[OP_CXKK], "V" + operands.first, "RANDOM_BYTE AND 0x" + operands.second);
}

/* Opcode Dxyn -> DRW Vx, Vy, nibble */
/* x: register number */
/* y: register number */
/* n: nibble */
std::string CPUC8Disassembler::ISIChip8Decoder::INST_Dxyn(uint16_t opcode) {
  auto operands = GetRegisters(opcode);
  return FormatBinaryOp(mnemonic_table[OP_DXYN], "V" + operands.first, "V" + operands.second + ", nibble");
}

/* Opcode Ex9E -> SKP Vx */
/* x: register number */
std::string CPUC8Disassembler::ISIChip8Decoder::INST_Ex9E(uint16_t opcode) {
  std::string operand = GetRegister(opcode);
  return FormatUnaryOp(mnemonic_table[OP_EX | 0x009E], "V" + operand);
}

/* Opcode ExA1 -> SKNP Vx */
/* x: register number */
std::string CPUC8Disassembler::ISIChip8Decoder::INST_ExA1(uint16_t opcode) {
  std::string operand = GetRegister(opcode);
  return FormatUnaryOp(mnemonic_table[OP_EX | 0x00A1], "V" + operand);
}

/* Opcode Fx07 -> LD Vx, DT */
/* x: register number */
std::string CPUC8Disassembler::ISIChip8Decoder::INST_Fx07(uint16_t opcode) {
  std::string operand = GetRegister(opcode);
  return FormatBinaryOp(mnemonic_table[OP_FX], "V" + operand, "DT");
}

/* Opcode Fx0A -> LD Vx, K */
/* x: register number */
std::string CPUC8Disassembler::ISIChip8Decoder::INST_Fx0A(uint16_t opcode) {
  std::string operand = GetRegister(opcode);
  return FormatBinaryOp(mnemonic_table[OP_FX], "V" + operand, "K");
}

/* Opcode Fx15 -> LD DT, Vx */
/* x: register number */
std::string CPUC8Disassembler::ISIChip8Decoder::INST_Fx15(uint16_t opcode) {
  std::string operand = GetRegister(opcode);
  return FormatBinaryOp(mnemonic_table[OP_FX], "DT", "V" + operand);
}

/* Opcode Fx18 -> LD ST, Vx */
/* x: register number */
std::string CPUC8Disassembler::ISIChip8Decoder::INST_Fx18(uint16_t opcode) {
  std::string operand = GetRegister(opcode);
  return FormatBinaryOp(mnemonic_table[OP_FX], "ST", "V" + operand);
}

/* Opcode Fx1E -> ADD I, Vx */
/* x: register number */
std::string CPUC8Disassembler::ISIChip8Decoder::INST_Fx1E(uint16_t opcode) {
  std::string operand = GetRegister(opcode);
  return FormatBinaryOp(mnemonic_table[OP_FX | 0x001E], "I", "V" + operand);
}

/* Opcode Fx29 -> LD F, Vx */
/* x: register number */
std::string CPUC8Disassembler::ISIChip8Decoder::INST_Fx29(uint16_t opcode) {
  std::string operand = GetRegister(opcode);
  return FormatBinaryOp(mnemonic_table[OP_FX], "F", "V" + operand);
}

/* Opcode Fx33 -> LD B, Vx*/
/* x: register number */
std::string CPUC8Disassembler::ISIChip8Decoder::INST_Fx33(uint16_t opcode) {
  std::string operand = GetRegister(opcode);
  return FormatBinaryOp(mnemonic_table[OP_FX], "B", "V" + operand);
}

/* Opcode Fx55 -> LD [I], Vx*/
/* x: register number */
std::string CPUC8Disassembler::ISIChip8Decoder::INST_Fx55(uint16_t opcode) {
  std::string operand = GetRegister(opcode);
  return FormatBinaryOp(mnemonic_table[OP_FX], "[I]", "V" + operand);
}

/* Opcode Fx65 -> LD Vx, [I] */
/* x: register number */
std::string CPUC8Disassembler::ISIChip8Decoder::INST_Fx65(uint16_t opcode) {
  std::string operand = GetRegister(opcode);
  return FormatBinaryOp(mnemonic_table[OP_FX], "V" + operand, "[I]");
}
