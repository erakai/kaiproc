#pragma once

#include <stdexcept>

template <typename T> class FrameBuffer
{
public:
  FrameBuffer(int w, int h) : w(w), h(h) { pix = new T[w * h]; };

  T get(int r, int c)
  {
    if ((r >= h || r < 0) || (c >= w || c < 0))
    {
      throw std::invalid_argument("out of bounds for framebuffer");
    }
    return pix[(h - 1 - r) * w + c];
  };

  void set(int r, int c, T val)
  {
    if ((r >= h || r < 0) || (c >= w || c < 0))
    {
      throw std::invalid_argument("out of bounds for framebuffer");
    }
    pix[(h - 1 - r) * w + c] = val;
  }

  void raster_rect(int x, int y, int rw, int rh, T val)
  {
    clip_rect(x, y, rw, rh, w, h);

    for (int r = y; r < y + rh; r++)
      for (int c = x; c < x + rw; c++)
        set(r, c, val);
  }

  void clip_rect(int &x, int &y, int &rw, int &rh, int w, int h)
  {
    if (y >= h || x >= w)
      return;
    if (x + rw >= w)
      rw = w - x;
    if (x < 0)
      x = 0;
    if (y + rh >= h)
      rh = h - y;
    if (y < 0)
      y = 0;
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
