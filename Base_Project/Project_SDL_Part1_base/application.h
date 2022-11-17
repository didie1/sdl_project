#pragma once

#include "ground.h"
#include "Project_SDL1.h"
#include "sheep.h"
#include "wolf.h"

class application {
private:
  // The following are OWNING ptrs
  SDL_Window* window_ptr_;
  SDL_Surface* window_surface_ptr_;
  SDL_Event window_event_;

  // Other attributes here, for example an instance of ground
  ground* my_ground;

public:
  application(unsigned int n_sheep, unsigned int n_wolf); // Ctor
  ~application();                                 // dtor

  int loop(unsigned int period); // main loop of the application.
                             // this ensures that the screen is updated
                             // at the correct rate.
                             // See SDL_GetTicks() and SDL_Delay() to enforce a
                             // duration the application should terminate after
                             // 'period' seconds
};
