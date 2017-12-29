#ifndef __CPU_H__
# define __CPU_H__

#include <iostream>
#include <string>
#include <cstdint>
#include <random>
#include "memory.h"
#include "gpu.h"
#include "controller.h"

/* Central processing unit of the Chip8 emulator */
class CPUChip8 {
 public:
 CPUChip8()
   : pc(0x200), I(0), sp(0), dt(0), st(0), isi(*this), id("cpu") {}

  bool EmulateCycle(RAMChip8& mmu,
		    GPUChip8& gpu,
		    CUChip8& cui);

  void DecrementTimers();

 private:
  /* Program counter stores the currently executing address */
  uint16_t pc;

  /* Stores memory addresses */
  uint16_t I;

  /* Stack pointer points to the topmost address of the stack */
  uint8_t sp;

  /* Registers named from V0 to VF */
  uint8_t v_registers[16];

  /* Delay timer register */
  uint8_t dt;

  /* Sound timer register */
  uint8_t st;

  /* Instruction set implementation */
  class ISIChip8 {

  public:
  ISIChip8(CPUChip8 &outer) : cpu(outer) {}
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

    /* INST_ contains instruction's implementation */
    void INST_00E0(GPUChip8& gpu);
    void INST_00EE(RAMChip8& mmu);
    void INST_1NNN(const uint16_t opcode);
    void INST_2NNN(RAMChip8& mmu, const uint16_t opcode);
    void INST_3xkk(const uint16_t opcode);
    void INST_4xkk(const uint16_t opcode);
    void INST_5xy0(const uint16_t opcode);
    void INST_6xkk(const uint16_t opcode);
    void INST_7xkk(const uint16_t opcode);
    void INST_8xy0(const uint16_t opcode);
    void INST_8xy1(const uint16_t opcode);
    void INST_8xy2(const uint16_t opcode);
    void INST_8xy3(const uint16_t opcode);
    void INST_8xy4(const uint16_t opcode);
    void INST_8xy5(const uint16_t opcode);
    void INST_8xy6(const uint16_t opcode);
    void INST_8xy7(const uint16_t opcode);
    void INST_8xyE(const uint16_t opcode);
    void INST_9xy0(const uint16_t opcode);
    void INST_ANNN(const uint16_t opcode);
    void INST_BNNN(const uint16_t opcode);
    void INST_Cxkk(const uint16_t opcode);
    void INST_Dxyn(GPUChip8& gpu,
		   RAMChip8& mmu,
		   const uint16_t opcode);
    void INST_Ex9E(CUChip8& cui, const uint16_t opcode);
    void INST_ExA1(CUChip8& cui, const uint16_t opcode);
    void INST_Fx07(const uint16_t opcode);
    void INST_Fx0A(CUChip8& cui, const uint16_t opcode);
    void INST_Fx15(const uint16_t opcode);
    void INST_Fx18(const uint16_t opcode);
    void INST_Fx1E(const uint16_t opcode);
    void INST_Fx29(const uint16_t opcode);
    void INST_Fx33(RAMChip8& mmu, const uint16_t opcode);
    void INST_Fx55(RAMChip8& mmu, const uint16_t opcode);
    void INST_Fx65(RAMChip8& mmu, const uint16_t opcode);

  private:
    CPUChip8& cpu;
  };

  void IncrementPC(const uint nb_increment);
  uint16_t FetchOpcode(const RAMChip8 & mmu) const;
  bool InterpretOpcode(RAMChip8& mmu,
		       GPUChip8& gpu,
		       CUChip8& cui);

  ISIChip8 isi;
  std::mt19937 rng;
  std::string id;
};

#endif /* __CPU_H__ */
