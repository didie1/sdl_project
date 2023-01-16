#include "Project_SDL.h"
#include <stdio.h>
#include <string>


int main(int argc, char* argv[]) {

  std::cout << "Starting up the application" << std::endl;

  if (argc != 4)
    throw std::runtime_error("To launch, type in three arguments - "
                             "number of sheep, number of wolves, "
                             "simulation time\n");

  init();

  srand(time(NULL));

  std::cout << "Initilization OK" << std::endl;

  application my_app = application(std::stoul(argv[1]), std::stoul(argv[2]));

  std::cout << "Window" << std::endl;

  int loop_val = my_app.loop(std::stoul(argv[3]));

  std::cout << "Exiting" << loop_val << std::endl;

  SDL_Quit();

  return loop_val;
}
