// SDL_Test.cpp: Definiert den Einstiegspunkt für die Anwendung.
//

#include "Project_SDL1.h"

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <numeric>
#include <random>
#include <string>

void init() {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO) < 0)
    throw std::runtime_error("init():" + std::string(SDL_GetError()));

  // Initialize PNG loading
  int imgFlags = IMG_INIT_PNG;
  if (!(IMG_Init(imgFlags) & imgFlags))
    throw std::runtime_error("init(): SDL_image could not initialize! "
                             "SDL_image Error: " +
                             std::string(IMG_GetError()));
}

namespace {
// Defining a namespace without a name -> Anonymous workspace
// Its purpose is to indicate to the compiler that everything
// inside of it is UNIQUELY used within this source file.

SDL_Surface* load_surface_for(const char* path,
                              SDL_Surface* window_surface_ptr) {
  // Helper function to load a png for a specific surface
  // See SDL_ConvertSurface
  SDL_Surface* img = IMG_Load(path);
  if (img == NULL) {
    std::cout << "Bug IMG LOAD" << std::endl;
    return NULL;
  }

  SDL_Surface* ret = SDL_ConvertSurface(img, window_surface_ptr->format, 0);
  if (ret == NULL) {
    std::cout << "BUG CONVERT SURFACE" << std::endl;
    return NULL;
  }

  SDL_FreeSurface(img);
  return ret;
}
} // namespace

float get_rand_float(int low, int high) {
    return low + rand() / (RAND_MAX / (high - low + 1) + 1);
}


animal::animal(const std::string& file_path, SDL_Surface* window_surface_ptr) {
  this->window_surface_ptr_ = window_surface_ptr;
  
  this->file_path = file_path;
  char * S = new char[file_path.length() + 1];
  for (size_t i = 0; i < file_path.length(); i++)
  {
    S[i] = file_path[i];
  }
  S[file_path.length()] = 0;
  this->image_ptr_ = load_surface_for(S, window_surface_ptr);

  // 0 + boundary < x < frame_width - boundary
  // 0 + boundary < y < frame_height - boundary
  this->pos = Vector2{get_rand_float(frame_boundary, frame_width - frame_boundary - this->image_ptr_->w),
                      get_rand_float(frame_boundary, frame_height - frame_boundary - this->image_ptr_->h)};
  this->spd = Vector2{get_rand_float(-40, 40), get_rand_float(-40, 40)};
}

animal::~animal(){
  // C'est pas a animal de free le pointeur
  SDL_FreeSurface(this->image_ptr_);
}

void animal::draw() {
  SDL_Rect dst_rect = SDL_Rect{int(this->pos.x), int(this->pos.y), int(this->pos.x + this->image_ptr_->w), int(this->pos.y + this->image_ptr_->h)};
  SDL_BlitSurface(this->image_ptr_, NULL, this->window_surface_ptr_, &dst_rect);
}
