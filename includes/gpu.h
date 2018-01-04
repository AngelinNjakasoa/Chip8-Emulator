#ifndef __GPUCHIP8_H__
# define __GPUCHIP8_H__

#include <algorithm>
#include <string>
#include <SDL2/SDL.h>

/* Emulates Chip8 display */
/* Work in progress */
class GPUChip8 {
 public:

 GPUChip8()
   :  height(32), width(64), screen_buffer(nullptr), refresh(false), id("gpu") {
    Initialize();
  }

  ~GPUChip8() {
    if (screen_buffer != nullptr) {
      delete[] screen_buffer;
      screen_buffer = nullptr;
    }
    SDL_DestroyWindow(window);
  }

  void Initialize() {
    screen_buffer = new uint8_t[width * height];
    std::fill_n(screen_buffer, width * height, 0);
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Chip8", 0, 0, 640, 320, SDL_WINDOW_SHOWN);
  }

  void SetRefresh(bool value) {
    refresh = value;
  }

  void DrawPixel(const uint8_t x, const uint8_t y, const uint8_t value) {
    if ((screen_buffer != nullptr) && (x + y * width < (width * height)))
      screen_buffer[x + y * width] = value;
  }

  uint8_t GetPixel(const uint8_t x, const uint8_t y) const {
    return ((screen_buffer != nullptr) && ((x + y * width) < (width * height)))
      ? screen_buffer[x + y * width] : 0;
  }

  void ClearScreen() {
    std::fill_n(screen_buffer, width * height, 0);
  }

  void PrintScreen() const {
    if ((screen_buffer != nullptr))
      for (uint y = 0; y < height; ++y) {
	for (uint x = 0; x < width; ++x) {
	  if (GetPixel(x, y) == 1)
	    std::cout << 'x';
	  else
	    std::cout << '_';
	}
	std::cout << std::endl;
      }
    std::cout << std::endl << std::endl;
  }

 private:

  /* Not copyable */
  GPUChip8& operator=(const GPUChip8&) = delete;

  /* Not copyable */
  GPUChip8(const GPUChip8&) = delete;

  SDL_Window* window;
  const uint8_t height;
  const uint8_t width;
  uint8_t *screen_buffer;
  bool refresh;
  std::string id;
};

#endif /* __GPUCHIP8_H__ */
