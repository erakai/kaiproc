#pragma once

#include "SDL_pixels.h"
#include "gui/display.hpp"
#include <cstdint>

struct Color
{
  uint8_t r = 0;   // 0 to 255
  uint8_t g = 0;   // 0 to 255
  uint8_t b = 0;   // 0 to 255
  uint8_t a = 255; // 0 to 255

  Color operator*(const float c) const
  {
    int new_r = static_cast<int>(r * c);
    if (new_r > 255)
      new_r = 255;
    if (new_r < 0)
      new_r = 0;
    int new_g = static_cast<int>(g * c);
    if (new_g > 255)
      new_g = 255;
    if (new_g < 0)
      new_g = 0;
    int new_b = static_cast<int>(b * c);
    if (new_b > 255)
      new_b = 255;
    if (new_b < 0)
      new_b = 0;

    return {static_cast<uint8_t>(new_r), static_cast<uint8_t>(new_g),
            static_cast<uint8_t>(new_b), a};
  }
};

const Color cwhite = {255, 255, 255, 255};
const Color cred = {255, 0, 0, 255};
const Color cgreen = {0, 255, 0, 255};
const Color cblue = {0, 0, 255, 255};
const Color cblack = {0, 0, 0, 255};

inline uint32_t color_to_int(Color c)
{
  // Returns a uint32_t in the form of 0xAABBGGRR
  return SDL_MapRGBA(PIXEL_FORMAT, c.r, c.g, c.b, c.a);
}
