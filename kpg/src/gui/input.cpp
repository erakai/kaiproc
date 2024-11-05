#include "gui/input.hpp"
#include "SDL_keycode.h"
#include "imgui.h"

namespace input
{

// Returns true if the gui loop should continue
bool poll_event_loop()
{
  ImGuiIO &io = ImGui::GetIO();

  SDL_Event e;
  bool quit = false;
  while (SDL_PollEvent(&e))
  {
    if (e.type == SDL_QUIT)
    {
      quit = true;
    }

    if (!io.WantCaptureKeyboard)
    {
      if (e.type == SDL_KEYDOWN)
      {
        if (e.key.keysym.sym == SDLK_ESCAPE)
        {
          quit = true;
        }
      }
    }
  }

  return !quit;
}

} // namespace input
