#include "c8_disassembler.h"

void CPUC8Disassembler::LoadBinary(const char* path) {
  loader.LoadROM(path);
  char* buffer = loader.GetFileBuffer();
  buffer_size = loader.GetBufferSize();
  byte_stream = new uint8_t[buffer_size];
  for (uint16_t i = 0; i < buffer_size; ++i) {
    byte_stream[i] = static_cast<uint8_t>(buffer[i]);
  }
  std::cout << std::endl;
}

uint16_t CPUC8Disassembler::GetOpcodeFromByteStream() {
  return (byte_stream[offset] << 8) | byte_stream[offset + 1];
}

bool CPUC8Disassembler::DisassembleOpcode() {
  uint16_t opcode = GetOpcodeFromByteStream();

  switch (opcode & 0xF000) {
  case CPUC8Disassembler::ISIChip8Decoder::OPCODE::OP_0NNN:
    switch(opcode) {
    case 0x00E0:
      isi_decoder.INST_00E0(opcode);
      MoveOffsetForward(1);
      break;
    case 0x00EE:
      isi_decoder.INST_00EE(opcode);
      MoveOffsetForward(1);
      break;
    default:
      MoveOffsetForward(1);
      std::cerr << "Unknown opcode from OP_0NNN:" << std::hex << static_cast<int>(opcode) << std::endl;
    }
    break;
  case CPUC8Disassembler::ISIChip8Decoder::OPCODE::OP_1NNN:
    isi_decoder.INST_1NNN(opcode);
    MoveOffsetForward(1);
    break;
  case CPUC8Disassembler::ISIChip8Decoder::OPCODE::OP_2NNN:
    isi_decoder.INST_2NNN(opcode);
    MoveOffsetForward(1);
    break;
  case CPUC8Disassembler::ISIChip8Decoder::OPCODE::OP_3XKK:
    isi_decoder.INST_3xkk(opcode);
    MoveOffsetForward(1);
    break;
  case CPUC8Disassembler::ISIChip8Decoder::OPCODE::OP_4XKK:
    isi_decoder.INST_4xkk(opcode);
    MoveOffsetForward(1);
    break;
  case CPUC8Disassembler::ISIChip8Decoder::OPCODE::OP_5XY0:
    isi_decoder.INST_5xy0(opcode);
    MoveOffsetForward(1);
    break;
  case CPUC8Disassembler::ISIChip8Decoder::OPCODE::OP_6XKK:
    isi_decoder.INST_6xkk(opcode);
    MoveOffsetForward(1);
    break;
  case CPUC8Disassembler::ISIChip8Decoder::OPCODE::OP_7XKK:
    isi_decoder.INST_7xkk(opcode);
    MoveOffsetForward(1);
    break;
  case CPUC8Disassembler::ISIChip8Decoder::OPCODE::OP_8XY:
    switch (opcode & 0x000F) {
    case 0x0000:
      isi_decoder.INST_8xy0(opcode);
      MoveOffsetForward(1);
      break;
    case 0x0001:
      isi_decoder.INST_8xy1(opcode);
      MoveOffsetForward(1);
      break;
    case 0x0002:
      isi_decoder.INST_8xy2(opcode);
      MoveOffsetForward(1);
      break;
    case 0x0003:
      isi_decoder.INST_8xy3(opcode);
      MoveOffsetForward(1);
      break;
    case 0x0004:
      isi_decoder.INST_8xy4(opcode);
      MoveOffsetForward(1);
      break;
    case 0x0005:
      isi_decoder.INST_8xy5(opcode);
      MoveOffsetForward(1);
      break;
    case 0x0006:
      isi_decoder.INST_8xy6(opcode);
      MoveOffsetForward(1);
      break;
    case 0x0007:
      isi_decoder.INST_8xy7(opcode);
      MoveOffsetForward(1);
      break;
    case 0x000E:
      isi_decoder.INST_8xyE(opcode);
      MoveOffsetForward(1);
      break;

    default:
      MoveOffsetForward(1);
      std::cerr << "Unknown OP_8: " << std::hex << static_cast<int>(opcode) << std::endl;
    }
    break;
  case CPUC8Disassembler::ISIChip8Decoder::OPCODE::OP_9XY:
    isi_decoder.INST_9xy0(opcode);
    MoveOffsetForward(1);
    break;
  case CPUC8Disassembler::ISIChip8Decoder::OPCODE::OP_ANNN:
    isi_decoder.INST_ANNN(opcode);
    MoveOffsetForward(1);
    break;
  case CPUC8Disassembler::ISIChip8Decoder::OPCODE::OP_BNNN:
    isi_decoder.INST_BNNN(opcode);
    MoveOffsetForward(1);
    break;
  case CPUC8Disassembler::ISIChip8Decoder::OPCODE::OP_CXKK:
    isi_decoder.INST_Cxkk(opcode);
    MoveOffsetForward(1);
    break;
  case CPUC8Disassembler::ISIChip8Decoder::OPCODE::OP_DXYN:
    isi_decoder.INST_Dxyn(opcode);
    MoveOffsetForward(1);
    break;
  case CPUC8Disassembler::ISIChip8Decoder::OPCODE::OP_EX:
    switch (opcode & 0x00FF) {
    case 0x009E:
      isi_decoder.INST_Ex9E(opcode);
      MoveOffsetForward(1);
      break;
    case 0x00A1:
      isi_decoder.INST_ExA1(opcode);
      MoveOffsetForward(1);
      break;
    default:
      MoveOffsetForward(1);
      std::cerr << "Unknown OP_E: " << std::hex << static_cast<int>(opcode) << std::endl;
    }
    break;
  case CPUC8Disassembler::ISIChip8Decoder::OPCODE::OP_FX:
    switch (opcode & 0x00FF) {
    case 0x0007:
      isi_decoder.INST_Fx07(opcode);
      MoveOffsetForward(1);
      break;
    case 0x000A:
      isi_decoder.INST_Fx0A(opcode);
      MoveOffsetForward(1);
      break;
    case 0x0015:
      isi_decoder.INST_Fx15(opcode);
      MoveOffsetForward(1);
      break;
    case 0x0018:
      isi_decoder.INST_Fx18(opcode);
      MoveOffsetForward(1);
      break;
    case 0x001E:
      isi_decoder.INST_Fx1E(opcode);
      MoveOffsetForward(1);
      break;
    case 0x0029:
      isi_decoder.INST_Fx29(opcode);
      MoveOffsetForward(1);
      break;
    case 0x0033:
      isi_decoder.INST_Fx33(opcode);
      MoveOffsetForward(1);
      break;
    case 0x0055:
      isi_decoder.INST_Fx55(opcode);
      MoveOffsetForward(1);
      break;
    case 0x0065:
      isi_decoder.INST_Fx65(opcode);
      MoveOffsetForward(1);
      break;
    default:
      MoveOffsetForward(1);
      std::cerr << "Unknown OP_F: " << std::hex << static_cast<int>(opcode) << std::endl;
    }
    break;

  default:
    MoveOffsetForward(1);
    std::cerr << "CPU: unrecognized opcode: " << std::hex << static_cast<int>(opcode) << std::endl;
    return false;
  }
  return true;
}

void CPUC8Disassembler::Disassemble() {
  while ((offset < buffer_size) && (DisassembleOpcode() == true))
    ;
}

int CPUC8Disassembler::GetBufferSize() {
  return loader.GetBufferSize();
}

uint16_t CPUC8Disassembler::GetOffset() {
  return offset;
}

uint16_t CPUC8Disassembler::MoveOffsetForward(const uint16_t incr_value) {
  offset += (incr_value * sizeof(uint16_t));
  return offset;
}

uint16_t CPUC8Disassembler::MoveOffsetBackward(const uint16_t decr_value) {
  offset -= (decr_value * sizeof(uint16_t));
  return offset;
}

uint16_t CPUC8Disassembler::ResetOffset() {
  offset = 0;
  return offset;
}
