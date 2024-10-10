#include "gui/input.hpp"

namespace input
{

// Returns true if the gui loop should continue
bool poll_event_loop()
{
  SDL_Event e;
  bool quit = false;
  while (!quit)
  {
    while (SDL_PollEvent(&e))
    {
      if (e.type == SDL_QUIT)
      {
        quit = true;
      }
    }
  }

  return !quit;
}

} // namespace input
