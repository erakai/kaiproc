#pragma once

#include <cstdint>

template <typename T> class FrameBuffer
{
public:
  FrameBuffer(int w, int h) : w(w), h(h) { pix = new uint32_t[w * h]; };

  T get(int r, int c) { return pix[(h - 1 - r) * w + c]; };
  void set(int r, int c, T it) { pix[(h - 1 - r) * w + c] = it; }

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
