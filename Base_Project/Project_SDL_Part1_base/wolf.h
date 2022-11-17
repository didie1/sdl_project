#pragma once

#include "Project_SDL1.h"

class wolf : public animal {
  public:
    wolf(SDL_Surface *window_surface_ptr) : animal::animal("media/wolf.png", window_surface_ptr){}
    void move() final;
  // implement functions that are purely virtual in base class
};
