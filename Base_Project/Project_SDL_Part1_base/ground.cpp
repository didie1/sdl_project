#include "ground.h"

ground::ground(SDL_Surface* window_surface_ptr)
{
    this->window_surface_ptr_ = window_surface_ptr;
}

ground::~ground()
{
    SDL_FreeSurface(this->window_surface_ptr_);
}

void ground::add_animal(animal* a)
{
    this->animals.push_back(a);
}

void ground::update()
{
  for (unsigned i = 0; i < this->animals.size(); ++i) {
      animals[i]->move();
      animals[i]->draw();
  }
    
}
