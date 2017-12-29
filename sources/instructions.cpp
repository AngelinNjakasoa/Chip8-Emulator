#include "cpu.h"

/* Clear the screen */
void CPUChip8::ISIChip8::INST_00E0(GPUChip8& gpu) {
  gpu.ClearScreen();
  cpu.IncrementPC(1);
  gpu.SetRefresh(true);
}

void CPUChip8::ISIChip8::INST_00EE(RAMChip8& mmu) {
  cpu.pc = mmu.stack[cpu.sp];
  --cpu.sp;
  cpu.IncrementPC(1);
}

/* Jump to NNN */
/* Set pc to NNN */
void CPUChip8::ISIChip8::INST_1NNN(const uint16_t opcode) {
  cpu.pc = opcode & 0x0FFF;
}

/* Call NNN */
/* Saves pc on top of the stack and jump to NNN */
void CPUChip8::ISIChip8::INST_2NNN(RAMChip8& mmu, const uint16_t opcode) {
  ++cpu.sp;
  mmu.stack[cpu.sp] = cpu.pc;
  cpu.pc = opcode & 0x0FFF;
}

/* Skip instruction if Vx == kk */
void CPUChip8::ISIChip8::INST_3xkk(const uint16_t opcode) {
  if (cpu.v_registers[(opcode & 0x0F00)] == (opcode & 0x00FF)) {
    cpu.IncrementPC(2);
    return ;
  }
  cpu.IncrementPC(1);
}

/* Skip the instruction if Vx != kk */
void CPUChip8::ISIChip8::INST_4xkk(const uint16_t opcode) {
  if (cpu.v_registers[(opcode & 0x0F00) >> 8] != (opcode & 0x00FF)) {
    cpu.IncrementPC(2);
    return ;
  }
  cpu.IncrementPC(1);
}

/* Skip the instruction if Vx == Vy */
void CPUChip8::ISIChip8::INST_5xy0(const uint16_t opcode) {
  if (cpu.v_registers[(opcode & 0x0F00) >> 8] == cpu.v_registers[(opcode & 0x00F0) >> 4]) {
    cpu.IncrementPC(2);
    return ;
  }
  cpu.IncrementPC(1);
}

/* Set Vx to kk */
void CPUChip8::ISIChip8::INST_6xkk(const uint16_t opcode) {
  cpu.v_registers[(opcode & 0x0F00) >> 8] = opcode & 0x00FF;
  cpu.IncrementPC(1);
}

/* Set Vx = Vx + kk */
void CPUChip8::ISIChip8::INST_7xkk(const uint16_t opcode) {
  cpu.v_registers[(opcode & 0x0F00) >> 8] += opcode & 0x00FF;
  cpu.IncrementPC(1);
}

/* Set Vx = Vy */
void CPUChip8::ISIChip8::INST_8xy0(const uint16_t opcode) {
  cpu.v_registers[(opcode & 0x0F00) >> 8] = cpu.v_registers[(opcode & 0x00F0) >> 4];
  cpu.IncrementPC(1);
}

/* Set Vx = Vx or Vy */
void CPUChip8::ISIChip8::INST_8xy1(const uint16_t opcode) {
  cpu.v_registers[(opcode & 0x0F00) >> 8] |= cpu.v_registers[(opcode & 0x00F0) >> 4];
  cpu.IncrementPC(1);
}

/* Set Vx = Vx and Vy */
void CPUChip8::ISIChip8::INST_8xy2(const uint16_t opcode) {
  cpu.v_registers[(opcode & 0x0F00) >> 8] &= cpu.v_registers[(opcode & 0x00F0) >> 4];
  cpu.IncrementPC(1);
}

/* Set Vx = Vx xor Vy */
void CPUChip8::ISIChip8::INST_8xy3(const uint16_t opcode) {
  cpu.v_registers[(opcode & 0x0F00) >> 8] ^= cpu.v_registers[(opcode & 0x00F0) >> 4];
  cpu.IncrementPC(1);
}

/* Set Vx = Vx + Vy, set VF = carry */
void CPUChip8::ISIChip8::INST_8xy4(const uint16_t opcode) {
  cpu.v_registers[(opcode & 0x0F00) >> 8] += cpu.v_registers[(opcode & 0x00F0) >> 4];
  cpu.IncrementPC(1);
}

/* Set Vx = Vx - Vy, set VF = carry */
void CPUChip8::ISIChip8::INST_8xy5(const uint16_t opcode) {
  cpu.v_registers[(opcode & 0x0F00) >> 8] -= cpu.v_registers[(opcode & 0x00F0) >> 4];
  cpu.IncrementPC(1);
}

/* Set Vx = Vx >> 1, if lsb == 1 then VF = 1 else VF = 0 */
void CPUChip8::ISIChip8::INST_8xy6(const uint16_t opcode) {
  cpu.v_registers[0xf] = opcode & 0x1;
  cpu.v_registers[(opcode & 0x0F00) >> 8] >>= 1;
  cpu.IncrementPC(1);
}

/* Set Vx = Vx - Vy, VF = NOT borrow */
void CPUChip8::ISIChip8::INST_8xy7(const uint16_t opcode) {
  if (cpu.v_registers[(opcode & 0x0F00) >> 8] > cpu.v_registers[(opcode & 0x00F0) >> 4]) {
    cpu.v_registers[0xf] = 1;
  } else {
    cpu.v_registers[0xf] = 0;
  }
  cpu.v_registers[(opcode & 0x0F00) >> 8] -= cpu.v_registers[(opcode & 0x00F0) >> 4];
  cpu.IncrementPC(1);
}

/* Set Vx = Vx << 1, if msb == 1 then VF = 1 else VF = 0 */
void CPUChip8::ISIChip8::INST_8xyE(const uint16_t opcode) {
  cpu.v_registers[0xf] = cpu.v_registers[(opcode & 0x0F00) >> 8] >> 7;
  cpu.v_registers[(opcode & 0x0F00) >> 8] <<= 1;
  cpu.IncrementPC(1);
}

/* Skip the next instruction if Vx != Vy */
void CPUChip8::ISIChip8::INST_9xy0(const uint16_t opcode) {
  if (cpu.v_registers[(opcode & 0x0F00) >> 8] != cpu.v_registers[(opcode & 0x00F0) >> 4]) {
    cpu.IncrementPC(2);
  }
  cpu.IncrementPC(1);
}

/* Set I = nnn */
void CPUChip8::ISIChip8::INST_ANNN(const uint16_t opcode) {
  cpu.I = opcode & 0x0FFF;
  cpu.IncrementPC(1);
}

/* Jump to location nnn + V0 */
void CPUChip8::ISIChip8::INST_BNNN(const uint16_t opcode) {
  cpu.pc = (opcode & 0xFFF) + cpu.v_registers[0];
}

/* Set Vx = random_byte and kk */
void CPUChip8::ISIChip8::INST_Cxkk(const uint16_t opcode) {
  uint8_t random_byte = 0;

  cpu.rng.seed(std::random_device()());
  std::uniform_int_distribution<std::mt19937::result_type> dist256(0,255);
  random_byte = dist256(cpu.rng);
  cpu.v_registers[(opcode & 0x0F00) >> 8] = random_byte & (opcode & 0x00FF);
  cpu.IncrementPC(1);
}

/* Display n byte sprite starting at memory location I at (Vx, Vy) */
/* Set VF = collision */
void CPUChip8::ISIChip8::INST_Dxyn(GPUChip8& gpu, RAMChip8& mmu, const uint16_t opcode) {
  uint16_t x_coord = cpu.v_registers[(opcode & 0x0F00) >> 8];
  uint16_t y_coord = cpu.v_registers[(opcode & 0x00F0) >> 4];
  uint16_t height = opcode & 0x000F;
  uint16_t pixel = 0;

  cpu.v_registers[0xF] = 0;
  for (int y_offset = 0; y_offset < height; y_offset++) {
    pixel = mmu.memory[cpu.I + y_offset];
    for(int x_offset = 0; x_offset < 8; x_offset++) {
      if((pixel & (0x80 >> x_offset)) != 0) {
	uint16_t tmp_pixel = gpu.GetPixel(x_coord + x_offset, y_coord + y_offset);
	if(tmp_pixel == 1) {
	  cpu.v_registers[0xF] = 1;
	}
	gpu.DrawPixel(x_coord + x_offset, y_coord + y_offset, tmp_pixel ^ 1);
      }
    }
  }
  cpu.IncrementPC(1);
  gpu.SetRefresh(true);
}

/* Skip the next instruction if key with the value Vx is pressed */
void CPUChip8::ISIChip8::INST_Ex9E(CUChip8& cui, const uint16_t opcode) {
  if (cui.GetKey(cpu.v_registers[(opcode & 0x0F00) >> 8]) != 0) {
    cpu.IncrementPC(2);
    return ;
  }
  cpu.IncrementPC(1);
}

/* ExA1 - SKNP Vx */
/* Skip next instruction if key with the value of Vx is not pressed. */
void CPUChip8::ISIChip8::INST_ExA1(CUChip8& cui, const uint16_t opcode) {
  if (cui.GetKey(cpu.v_registers[(opcode & 0x0F00) >> 8]) == 0) {
    cpu.IncrementPC(2);
    return ;
  }
  cpu.IncrementPC(1);
}

/* Fx07 - LD Vx, DT */
/* Set Vx = delay timer value. */
void CPUChip8::ISIChip8::INST_Fx07(const uint16_t opcode) {
  cpu.v_registers[(opcode & 0x0F00) >> 8] = cpu.dt;
  cpu.IncrementPC(1);
}

/* Fx0A - LD Vx, K */
/* Wait for a key press, store the value of the key in Vx. */
/* All execution stops until a key is pressed, then the value of that key is stored in Vx. */
void CPUChip8::ISIChip8::INST_Fx0A(CUChip8& cui, const uint16_t opcode) {
  bool key_pressed = false;

  for (uint i = 0; i < 16; ++i) {
    auto key = cui.GetKey(i);
    if (key != 0) {
      cpu.v_registers[(opcode & 0x0F00) >> 8] = key;
      key_pressed = true;
    }
  }

  if (key_pressed != true)
    return ;
  cpu.IncrementPC(1);
}

/* Fx15 - LD DT, Vx */
/* Set delay timer = Vx. */
/* DT is set equal to the value of Vx. */
void CPUChip8::ISIChip8::INST_Fx15(const uint16_t opcode) {
  cpu.dt = cpu.v_registers[(opcode & 0x0F00) >> 8];
  cpu.IncrementPC(1);
}

/* Fx18 - LD ST, Vx */
/* Set sound timer = Vx. */
/* ST is set equal to the value of Vx. */
void CPUChip8::ISIChip8::INST_Fx18(const uint16_t opcode) {
  cpu.st = cpu.v_registers[(opcode & 0x0F00) >> 8];
  cpu.IncrementPC(1);
}

/* Fx1E - ADD I, Vx */
/* Set I = I + Vx. */
/* The values of I and Vx are added, and the results are stored in I. */
void CPUChip8::ISIChip8::INST_Fx1E(const uint16_t opcode) {
  if (cpu.I + cpu.v_registers[(opcode & 0x0F00) >> 8] > 0x0FFF)
    cpu.v_registers[0xF] = 1;
  else
    cpu.v_registers[0xF] = 0;
  cpu.I += cpu.v_registers[(opcode & 0x0F00) >> 8];
  cpu.IncrementPC(1);
}


/* Fx29 - LD F, Vx */
/* Set I = location of sprite for digit Vx. */
/* The value of I is set to the location for the hexadecimal */
/* sprite corresponding to the value of Vx. See section 2.4, Display, */
/* for more information on the Chip-8 hexadecimal font. */
void CPUChip8::ISIChip8::INST_Fx29(const uint16_t opcode) {
  cpu.I = cpu.v_registers[(opcode & 0x0F00) >> 8] * 0x5; // Padded by 5
  cpu.IncrementPC(1);
}

/* Fx33 - LD B, Vx */
/* Store BCD representation of Vx in memory locations I, I+1, and I+2. */
/* The interpreter takes the decimal value of Vx, and places the hundreds */
/* digit in memory at location in I, the tens digit at location I+1, */
/* and the ones digit at location I+2. */
void CPUChip8::ISIChip8::INST_Fx33(RAMChip8& mmu, const uint16_t opcode) {
  uint8_t vx_reg = cpu.v_registers[(opcode & 0x0F00) >> 8];
  mmu.memory[cpu.I] = vx_reg / 100; // isolate hundred digit
  mmu.memory[cpu.I + 1] = (vx_reg / 10) % 10; // isolate tens digit
  mmu.memory[cpu.I + 2] = (vx_reg % 100) % 10; // isolate last digit
  cpu.IncrementPC(1);
}

/* Fx55 - LD [I], Vx */
/* Store registers V0 through Vx in memory starting at location I. */
/* The interpreter copies the values of registers V0 through Vx into */
/* memory, starting at the address in I. */
void CPUChip8::ISIChip8::INST_Fx55(RAMChip8& mmu, const uint16_t opcode) {
  uint8_t nb_register = ((opcode & 0x0F00) >> 8);
  for (uint i = 0; i <= nb_register; ++i) {
    mmu.memory[cpu.I + i] = cpu.v_registers[i];
  }

  cpu.I += nb_register + 1;
  cpu.IncrementPC(1);
}

/* Fx65 - LD Vx, [I] */
/* Read registers V0 through Vx from memory starting at location I. */
/* The interpreter reads values from memory starting at location I */
/* into registers V0 through Vx. */
void CPUChip8::ISIChip8::INST_Fx65(RAMChip8& mmu, const uint16_t opcode) {
  uint8_t nb_register = ((opcode & 0x0F00) >> 8);
  for (uint i = 0; i <= nb_register; ++i) {
    cpu.v_registers[i] = mmu.memory[cpu.I + i];
  }

  cpu.I += nb_register + 1;
  cpu.IncrementPC(1);
}
