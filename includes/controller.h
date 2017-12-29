#ifndef __CONTROLLER_UNIT_H__
# define __CONTROLLER_UNIT_H__

#include <algorithm>
#include <string>

/* Emulates the keyboard */
/* TODO(Lemme): implement it :D */
class CUChip8 {
 public:

 CUChip8()
   : id("cu") {
    std::fill_n(keys_buffer, sizeof(keys_buffer), 0);
  }

  bool PollEvent() {
    if (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_KEYDOWN:
	switch (event.key.keysym.sym) {
	case SDLK_1:
	  keys_buffer[0x1] = 1;
	  break;
	case SDLK_2:
	  keys_buffer[0x2] = 1;
	  break;
	case SDLK_3:
	  keys_buffer[0x3] = 1;
	  break;
	case SDLK_4:
	  keys_buffer[0xC] = 1;
	  break;
	case SDLK_q:
	  keys_buffer[0x4] = 1;
	  break;
	case SDLK_w:
	  keys_buffer[0x5] = 1;
	  break;
	case SDLK_e:
	  keys_buffer[0x6] = 1;
	  break;
	case SDLK_r:
	  keys_buffer[0xD] = 1;
	  break;
	case SDLK_a:
	  keys_buffer[0x7] = 1;
	  break;
	case SDLK_s:
	  keys_buffer[0x8] = 1;
	  break;
	case SDLK_d:
	  keys_buffer[0x9] = 1;
	  break;
	case SDLK_f:
	  keys_buffer[0xE] = 1;
	  break;
	case SDLK_z:
	  keys_buffer[0xA] = 1;
	  break;
	case SDLK_x:
	  keys_buffer[0x0] = 1;
	  break;
	case SDLK_c:
	  keys_buffer[0xB] = 1;
	  break;
	case SDLK_v:
	  keys_buffer[0xF] = 1;
	  break;
	case SDLK_ESCAPE:
	  return true;
	}
      }
    }
    return false;
  }

  /* Set a value in the key buffer */
  void SetKey(uint8_t offset, uint8_t value) {
    if (offset <  sizeof(keys_buffer))
      keys_buffer[offset] = value;
  }

  /* Returns a value from key buffer */
  uint8_t GetKey(uint8_t offset) {
    if (offset < sizeof(keys_buffer))
      return keys_buffer[offset];
    return 0;
  }

 private:

  SDL_Event event;
  uint8_t keys_buffer[16];
  const std::string id;
};

#endif /* __CONTROLLER_UNIT_H__ */
