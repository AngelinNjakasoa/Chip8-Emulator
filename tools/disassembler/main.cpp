#include "c8_disassembler.h"

int main(int argc, char** argv) {
  if (argc > 1) {
    CPUC8Disassembler c8d;

    c8d.LoadBinary(argv[1]);
    c8d.Disassemble();
    return 0;
  } else {
    std::cerr << "Usage: "
	      << argv[0]
	      << " input_binary_file"
	      << std::endl;
  }
  return 1;
}
