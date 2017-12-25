#ifndef __EMULATOR_H__
# define __EMULATOR_H__

#include "cpu.h"
#include "memory.h"
#include "gpu.h"
#include "controller.h"
#include "loader.h"

/* Emulates Chip8 CPU, memory, graphics, sound and display */
class CHIP8Emulator {
 public:
 CHIP8Emulator() : quit(false) {}

  bool LoadROM(const char* file_path) {
    loader.LoadROM(file_path, mmu);
  }

  void PrintMemory(uint16_t from, uint16_t to) {
    for (uint16_t i = 0; (i + from) <= to; ++i) {
      std::cerr << std::hex << static_cast<int>(mmu.memory[i + from]);
    }
    std::cerr << std::endl;
  }

  void Emulate() {
    while (!quit) {
      cpu.EmulateCycle(mmu, gpu, cui);
      cpu.DecrementTimers();
      // TODO(Lemme): handle correctly the quit status
      quit = cui.PollEvent();
      std::system("clear");
      gpu.PrintScreen();
    }
  }

 private:
  CPUChip8 cpu;
  RAMChip8 mmu;
  GPUChip8 gpu;
  CUChip8 cui;
  LoaderC8 loader;
  bool quit;
};

#endif /* __EMULATOR_H__ */
