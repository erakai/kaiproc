#pragma once

#include <cstdint>

struct Color
{
  int r = 0;   // 0 to 255
  int g = 0;   // 0 to 255
  int b = 0;   // 0 to 255
  int a = 255; // 0 to 255

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

    return {new_r, new_g, new_b, a};
  }
};

inline uint32_t color_to_int(Color c)
{
  // Returns a uint32_t in the form of 0xAABBGGRR
  return (static_cast<uint32_t>(c.a) << 24) |
         (static_cast<uint32_t>(c.b) << 16) |
         (static_cast<uint32_t>(c.g) << 8) | static_cast<uint32_t>(c.r);
}

inline Color int_to_color(uint32_t i)
{
  Color c;
  c.r = (i >> 24) & 0xFF;
  c.g = (i >> 16) & 0xFF;
  c.b = (i >> 8) & 0xFF;
  c.a = i & 0xFF;
  return c;
}
