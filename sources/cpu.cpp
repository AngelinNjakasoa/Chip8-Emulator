#include "cpu.h"

/* MSB endian */
/* size of pc is 16bits */
/* size of memory cell is 8bits */
uint16_t CPUChip8::FetchOpcode(RAMChip8& mmu) {
  return mmu.memory[pc] << 8 | mmu.memory[pc + 1];
}

/* Increments the program counter */
void CPUChip8::IncrementPC(uint nb_increment) {
  pc += nb_increment * sizeof(pc);
}

/* Emulates a cycle */
/* Interprets opcode read from memory */
/* Refresh the display */
bool CPUChip8::InterpretOpcode(RAMChip8& mmu, GPUChip8& gpu, CUChip8& cui) {
  uint16_t opcode = FetchOpcode(mmu);

  switch (opcode & 0xF000) {
  case ISIChip8::OPCODE::OP_0NNN:
    switch(opcode) {
    case 0x00E0:
      std::cerr << "OP_00E0" << std::endl;
      isi.INST_00E0(gpu);
      break;
    case 0x00EE:
      std::cerr << "OP_0x00EE" << std::endl;
      isi.INST_00EE(mmu);
      break;
    default:
      std::cerr << "Unknown opcode from OP_0NNN" << std::endl;
    }
    break;
  case ISIChip8::OPCODE::OP_1NNN:
    isi.INST_1NNN(opcode);
    std::cerr << "OP_1" << std::endl;
    break;
  case ISIChip8::OPCODE::OP_2NNN:
    isi.INST_2NNN(mmu, opcode);
    std::cerr << "OP_2" << std::endl;
    break;
  case ISIChip8::OPCODE::OP_3XKK:
    isi.INST_3xkk(opcode);
    std::cerr << "OP_3" << std::endl;
    break;
  case ISIChip8::OPCODE::OP_4XKK:
    isi.INST_4xkk(opcode);
    std::cerr << "OP_4" << std::endl;
    break;
  case ISIChip8::OPCODE::OP_5XY0:
    isi.INST_5xy0(opcode);
    std::cerr << "OP_5" << std::endl;
    break;
  case ISIChip8::OPCODE::OP_6XKK:
    isi.INST_6xkk(opcode);
    std::cerr << "OP_6" << std::endl;
    break;
  case ISIChip8::OPCODE::OP_7XKK:
    isi.INST_7xkk(opcode);
    std::cerr << "OP_7" << std::endl;
    break;
  case ISIChip8::OPCODE::OP_8XY:
    std::cerr << "OP_8" << std::endl;
    switch (opcode & 0x000F) {
    case 0x0000:
      isi.INST_8xy0(opcode);
      break;
    case 0x0001:
      isi.INST_8xy1(opcode);
      break;
    case 0x0002:
      isi.INST_8xy2(opcode);
      break;
    case 0x0003:
      isi.INST_8xy3(opcode);
      break;
    case 0x0004:
      isi.INST_8xy4(opcode);
      break;
    case 0x0005:
      isi.INST_8xy5(opcode);
      break;
    case 0x0006:
      isi.INST_8xy6(opcode);
      break;
    case 0x0007:
      isi.INST_8xy7(opcode);
      break;
    case 0x000E:
      isi.INST_8xyE(opcode);
      break;

    default:
      std::cerr << "Unknown OP_8" << std::endl;
    }
    break;
  case ISIChip8::OPCODE::OP_9XY:
    isi.INST_9xy0(opcode);
    std::cerr << "OP_9" << std::endl;
    break;
  case ISIChip8::OPCODE::OP_ANNN:
    isi.INST_ANNN(opcode);
    std::cerr << "OP_A" << std::endl;
    break;
  case ISIChip8::OPCODE::OP_BNNN:
    isi.INST_BNNN(opcode);
    std::cerr << "OP_B" << std::endl;
    break;
  case ISIChip8::OPCODE::OP_CXKK:
    isi.INST_Cxkk(opcode);
    std::cerr << "OP_C" << std::endl;
    break;
  case ISIChip8::OPCODE::OP_DXYN:
    isi.INST_Dxyn(gpu, mmu, opcode);
    std::cerr << "OP_D" << std::endl;
    break;
  case ISIChip8::OPCODE::OP_EX:
    std::cerr << "OP_EX" << std::endl;
    switch (opcode & 0x00FF) {
    case 0x009E:
      isi.INST_Ex9E(cui, opcode);
      break;
    case 0x00A1:
      isi.INST_ExA1(cui, opcode);
      break;
    default:
      std::cerr << "Unknown OP_E" << std::endl;
    }
    break;
  case ISIChip8::OPCODE::OP_FX:
    std::cerr << "OP_F" << std::endl;
    switch (opcode & 0x00FF) {
    case 0x0007:
      isi.INST_Fx07(opcode);
      break;
    case 0x000A:
      isi.INST_Fx0A(cui, opcode);
      break;
    case 0x0015:
      isi.INST_Fx15(opcode);
      break;
    case 0x0018:
      isi.INST_Fx18(opcode);
      break;
    case 0x001E:
      isi.INST_Fx1E(opcode);
      break;
    case 0x0029:
      isi.INST_Fx29(opcode);
      break;
    case 0x0033:
      isi.INST_Fx33(mmu, opcode);
      break;
    case 0x0055:
      isi.INST_Fx55(mmu, opcode);
      break;
    case 0x0065:
      isi.INST_Fx65(mmu, opcode);
      break;
    default:
      std::cerr << "Unknown OP_F" << std::endl;
    }
    break;

  default:
    std::cerr << "CPU: unrecognized opcode" << std::endl;
    return false;
  }
  return true;
}

/* Timers are decremented at 60Hz */
void CPUChip8::DecrementTimers() {
  if (dt > 0) {
    --dt;
  }

  /* terminal beep for the sound */
  if (st > 0) {
    if (st == 1) {
      std::cout << '\07';
    }
    --st;
  }
}

/* Emulates a cycle */
/* Interprets opcode read from memory */
/* Refresh the display */
bool CPUChip8::EmulateCycle(RAMChip8& mmu, GPUChip8& gpu, CUChip8& cui) {
  bool state = false;
  state = InterpretOpcode(mmu, gpu, cui);
  return state;
}
