#include "application.h"

application::application(unsigned int n_sheep, unsigned int n_wolf) {
    this->window_ptr_ = SDL_CreateWindow("Barn Simulation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, frame_width, frame_height, SDL_WINDOW_SHOWN);
    if (this->window_ptr_ == NULL) {
      std::cout << std::string(SDL_GetError()) << std::endl;
      abort();
    }
    this->window_surface_ptr_ = SDL_GetWindowSurface(this->window_ptr_);
    if (this->window_surface_ptr_ == NULL) {
      std::cout << std::string(SDL_GetError()) << std::endl;
      abort();
    }
    this->my_ground = new ground(this->window_surface_ptr_);

    for (unsigned i = 0 ; i < n_sheep ; ++i)
        this->my_ground->add_animal(new sheep(this->window_surface_ptr_));

    for (unsigned i = 0; i < n_wolf ; ++i)
        this->my_ground->add_animal(new wolf(this->window_surface_ptr_));
}

application::~application() {
    delete(this->my_ground);
    SDL_FreeSurface(this->window_surface_ptr_);
    SDL_DestroyWindow(this->window_ptr_);
}

int application::loop(unsigned int period) {
    bool close = false;

    unsigned int elapsed_time = 0;

    while (!close && elapsed_time < period * 1000) {
        unsigned int loop_begin = SDL_GetTicks();
        while (SDL_PollEvent(&this->window_event_)) {
            switch (this->window_event_.type) {
                case SDL_QUIT:
                    close = true;
                    break;
            }
        }
        
        SDL_FillRect(this->window_surface_ptr_, NULL, SDL_MapRGB(this->window_surface_ptr_->format, 0, 255, 0));
        
        this->my_ground->update();
        
        SDL_UpdateWindowSurface(this->window_ptr_);
        unsigned int loop_end = SDL_GetTicks();
        unsigned int delta = loop_end - loop_begin;
        if (delta < frame_time * 1000) {
            SDL_Delay(frame_time * 1000 - delta);
            elapsed_time += frame_time * 1000;
        } else {
            elapsed_time += delta;
        }
        //SDL_Delay(frame_time * 1000);
  }

    return 0;
}
