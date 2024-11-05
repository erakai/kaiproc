#pragma once

#include "gui/framebuffer.hpp"

class Component
{
public:
  Component() {}
  virtual ~Component() {}

  virtual void render(FrameBuffer<uint32_t> fb, long delta) = 0;
  virtual void update(long delta) = 0;
};
