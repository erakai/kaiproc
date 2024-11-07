#include "gui/input.hpp"
#include "SDL_events.h"
#include "SDL_keycode.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"

namespace input
{

std::vector<std::function<void(SDL_Keycode key)>> key_callbacks;
std::vector<std::function<void(int type, int button, int x, int y, int wheel)>>
    mouse_callbacks;

int mouse_x = 0;
int mouse_y = 0;

// Returns true if the gui loop should continue
bool poll_event_loop()
{
  ImGuiIO &io = ImGui::GetIO();

  SDL_Event e;
  bool quit = false;
  while (SDL_PollEvent(&e))
  {
    ImGui_ImplSDL2_ProcessEvent(&e);

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
      else
      {
        for (auto func : key_callbacks)
        {
          func(e.key.keysym.sym);
        }
      }
    }

    if (!io.WantCaptureMouse)
    {
      if (e.type == SDL_MOUSEMOTION)
      {
        mouse_x = e.motion.x;
        mouse_y = e.motion.y;
      }
      if (e.type == SDL_MOUSEBUTTONUP || e.type == SDL_MOUSEBUTTONDOWN ||
          e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEWHEEL)
      {
        for (auto func : mouse_callbacks)
        {
          func(e.type, e.button.button, mouse_x, mouse_y, e.wheel.y);
        }
      }
    }
  }

  return !quit;
}

} // namespace input
