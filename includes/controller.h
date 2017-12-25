#ifndef __CONTROLLER_UNIT_H__
# define __CONTROLLER_UNIT_H__

#include <string>

/* Emulates the keyboard */
/* TODO(Lemme): implement it :D */
class CUChip8 {
 public:
 CUChip8()
   : id("cu") {
    for (uint i = 0; i < 16; ++i) {
      keys[i] = 0;
    }
  }

  bool PollEvent() {
    if (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_KEYDOWN:
	switch (event.key.keysym.sym) {
	case SDLK_1:
	  keys[0x1] = 1;
	  break;
	case SDLK_2:
	  keys[0x2] = 1;
	  break;
	case SDLK_3:
	  keys[0x3] = 1;
	  break;
	case SDLK_4:
	  keys[0xC] = 1;
	  break;
	case SDLK_q:
	  keys[0x4] = 1;
	  break;
	case SDLK_w:
	  keys[0x5] = 1;
	  break;
	case SDLK_e:
	  keys[0x6] = 1;
	  break;
	case SDLK_r:
	  keys[0xD] = 1;
	  break;
	case SDLK_a:
	  keys[0x7] = 1;
	  break;
	case SDLK_s:
	  keys[0x8] = 1;
	  break;
	case SDLK_d:
	  keys[0x9] = 1;
	  break;
	case SDLK_f:
	  keys[0xE] = 1;
	  break;
	case SDLK_z:
	  keys[0xA] = 1;
	  break;
	case SDLK_x:
	  keys[0x0] = 1;
	  break;
	case SDLK_c:
	  keys[0xB] = 1;
	  break;
	case SDLK_v:
	  keys[0xF] = 1;
	  break;
	case SDLK_ESCAPE:
	  return true;
	}
      }
    }
    return false;
  }

  SDL_Event event;
  uint8_t keys[16];
  std::string id;
};

#endif /* __CONTROLLER_UNIT_H__ */
