#include "chip8_emulator.h"

int main(int argc, char **argv) {
  if (argc > 1) {
    CHIP8Emulator c8;
    if (c8.LoadROM(argv[1]) == true) {
      c8.Emulate();
    }
    return 0;
  } else {
    std::cerr << "Usage: "
	      << argv[0]
	      << " input_rom"
	      << std::endl
	      << "\t input_rom: path to a chip8 ROM"
	      << std::endl;
  }
  return 1;
}
