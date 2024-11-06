#pragma once

#include "gui/camera.hpp"
#include "gui/framebuffer.hpp"

class Component
{
public:
  Component() {}
  virtual ~Component() {}

  virtual void render(FrameBuffer<uint32_t> fb, Camera camera, long delta) = 0;
  virtual void update(long delta) = 0;
};
