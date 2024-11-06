#pragma once

#include "SDL_render.h"
#include "gui/camera.hpp"
#include "gui/component.hpp"
#include "gui/framebuffer.hpp"

#include <string>

#define ImTextureID SDL_Texture *

extern SDL_PixelFormat *PIXEL_FORMAT;

class Display
{
public:
  Display(int screen_width, int screen_height, std::string title);

  void render(std::vector<std::shared_ptr<Component>> components, Camera camera,
              const long delta);
  bool is_initialized() { return initialized; }

  void close();

  SDL_Renderer *get_renderer() { return renderer; }

private:
  bool initialized = false;

  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;

  FrameBuffer<uint32_t> fb;
  SDL_Texture *frame_texture = nullptr;

  void initialize_imgui();
};
