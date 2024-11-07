#include "gui/display.hpp"
#include "SDL.h"

#include "SDL_image.h"
#include "SDL_video.h"
#include "gui/camera.hpp"
#include "gui/component.hpp"
#include "utils/logger.hpp"

#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

SDL_PixelFormat *PIXEL_FORMAT = nullptr;

Display::Display(int screen_width, int screen_height, std::string title)
    : fb(screen_width, screen_height)
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

  frame_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                                    SDL_TEXTUREACCESS_STREAMING, screen_width,
                                    screen_height);
  if (frame_texture == nullptr)
  {
    log_sdl("Error initializing framebuffer!", ll::CRITICAL);
    return;
  }

  initialize_imgui();

  initialized = true;
  log("Display initialized", ll::NOTE);

  // Retrieve pixel format
  SDL_RendererInfo info;
  SDL_GetRendererInfo(renderer, &info);
  if (info.num_texture_formats > 0)
  {
    PIXEL_FORMAT = SDL_AllocFormat(info.texture_formats[0]);
  }
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

  fb.destroy();
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  renderer = nullptr;
  window = nullptr;

  SDL_Quit();
}

void Display::render(std::vector<std::shared_ptr<Component>> components,
                     std::shared_ptr<Camera> camera, const long delta)
{
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);

  for (int i = 0; i < fb.w * fb.h; i++)
    fb.pix[i] = 0xFFFFFFFF;

  for (std::shared_ptr<Component> comp : components)
  {
    comp->render(fb, camera, delta);
  }

  SDL_UpdateTexture(frame_texture, NULL, fb.pix, fb.w * sizeof(uint32_t));
  SDL_RenderCopy(renderer, frame_texture, NULL, NULL);

  ImGui::Render();
  ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);

  SDL_RenderPresent(renderer);
}
