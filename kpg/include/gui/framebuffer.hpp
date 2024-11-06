#pragma once

#include <cstdint>
#include <stdexcept>

template <typename T> class FrameBuffer
{
public:
  FrameBuffer(int w, int h) : w(w), h(h) { pix = new uint32_t[w * h]; };

  T get(int r, int c)
  {
    if ((r >= h || r < 0) || (c >= w || c < 0))
    {
      throw std::invalid_argument("out of bounds for framebuffer");
    }
    return pix[(h - 1 - r) * w + c];
  };

  void set(int r, int c, T it)
  {
    if ((r >= h || r < 0) || (c >= w || c < 0))
    {
      throw std::invalid_argument("out of bounds for framebuffer");
    }
    pix[(h - 1 - r) * w + c] = it;
  }

  void clear()
  {
    for (int i = 0; i < w * h; i++)
      pix[i] = 0;
  }

  void destroy()
  {
    delete pix;
    pix = nullptr;
  }

  T *pix = nullptr;
  int w, h;
};
