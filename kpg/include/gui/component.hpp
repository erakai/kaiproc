#pragma once

#include "gui/camera.hpp"
#include "gui/framebuffer.hpp"
#include <memory>

class Component
{
public:
  Component() {}
  virtual ~Component() {}

  virtual void render(FrameBuffer<uint32_t> fb, std::shared_ptr<Camera> camera,
                      long delta) = 0;
  virtual void update(long delta) = 0;
};
