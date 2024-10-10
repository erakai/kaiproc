#pragma once

#include "SDL_render.h"
#include "gui/color.hpp"

#include <string>

#define ImTextureID SDL_Texture *

class Display
{
public:
  Display(int screen_width, int screen_height, std::string title,
          Color clear_color);

  void render(const long delta);
  bool is_initialized() { return initialized; }

  void close();

  SDL_Renderer *get_renderer() { return renderer; }

private:
  Color clear_color;
  bool initialized = false;

  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;

  void initialize_imgui();
};
