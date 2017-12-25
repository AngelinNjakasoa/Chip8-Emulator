#ifndef __LOADER_H__
# define __LOADER_H__

#include <fstream>
#include <string>

/* Load a ROM into chip8 emulator's memory */
class LoaderC8 {
 public:
 LoaderC8()
   : id("Loader"), rom_buffer(nullptr) {}

  ~LoaderC8() {
    if (rom_buffer != nullptr)
      delete[] rom_buffer;
  }

  /* Load a ROM file into memory */
  bool LoadROM(const char* file_path, RAMChip8& mmu) {
    int begin = 0;
    int end = 0;

    file.open(file_path, std::ifstream::in | std::ifstream::binary);
    if (file.is_open() != true) {
      std::cerr << "Error(Loader): cannot open file" << std::endl;
      return false;
    }

    begin = file.tellg();
    file.seekg(0, std::ios::end);
    end = file.tellg();
    buffer_size = end - begin;
    std::cout << "file_size: " << buffer_size << std::endl;

    file.seekg(0, std::ios::beg);
    rom_buffer = new char [buffer_size];
    file.read(rom_buffer, buffer_size);

    std::cout << "Read: " << file.gcount() << " characters" << std::endl;
    file.close();

    LoadToMemory(mmu);
    return true;
  }  

 private:
  const char* get_rom_buffer() const {
    return rom_buffer;
  }

  /* Load the rom_buffer into chip8 emulator's memory */
  bool LoadToMemory(RAMChip8& mmu) {
    if (buffer_size > (4096 - 512)) {
      std::cerr << "Error(loader): ROM too large" << std::endl;
      return false;
    }

    for (uint i = 0; i < buffer_size; ++i) {
      mmu.memory[i + 512] = static_cast<uint8_t>(rom_buffer[i]);
    }

    delete[] rom_buffer;
    rom_buffer = nullptr;
    return true;
  }

  std::ifstream file;
  std::string id;
  char *rom_buffer;
  int buffer_size;
};

#endif /* __LOADER_H__ */
