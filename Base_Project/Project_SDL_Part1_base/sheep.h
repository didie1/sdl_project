#pragma once

#include "Project_SDL1.h"

class sheep : public animal {
  public:
    sheep(SDL_Surface *window_surface_ptr) : animal::animal("media/sheep.png", window_surface_ptr){}
    void move() final;
  // implement functions that are purely virtual in base class
};
