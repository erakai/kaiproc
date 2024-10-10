#include "gui/display.hpp"
#include "SDL.h"

#include "SDL_image.h"
#include "SDL_video.h"
#include "utils/logger.hpp"

#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

Display::Display(int screen_width, int screen_height, std::string title,
                 Color clear_color)
    : clear_color(clear_color)
{
  if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
  {
    log_sdl("Error initializing SDL!", ll::CRITICAL);
    return;
  }

  if (IMG_Init(IMG_INIT_PNG) < 0)
  {
    log_sdl("Error initializing SDL_image!", ll::CRITICAL);
    return;
  }

  SDL_CreateWindowAndRenderer(screen_width, screen_height, SDL_WINDOW_SHOWN,
                              &window, &renderer);

  if (window == nullptr || renderer == nullptr)
  {
    log_sdl("Error creating window and renderer!", ll::CRITICAL);
    return;
  }

  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  SDL_SetWindowTitle(window, title.c_str());

  initialize_imgui();

  initialized = true;
  log("Display initialized", ll::NOTE);
}

void Display::initialize_imgui()
{
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableGamepad;            // Enable Gamepad Controls
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // IF using Docking Branch

  ImGui::StyleColorsDark();

  ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
  ImGui_ImplSDLRenderer2_Init(renderer);
}

void Display::close()
{
  ImGui_ImplSDLRenderer2_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();

  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  renderer = nullptr;
  window = nullptr;

  SDL_Quit();
}

void Display::render(const long delta)
{
  SDL_SetRenderDrawColor(renderer, clear_color.r, clear_color.g, clear_color.b,
                         clear_color.opacity);
  SDL_RenderClear(renderer);

  // render components
  // ...

  ImGui::Render();
  ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);

  SDL_RenderPresent(renderer);
}
