#pragma once

#include "gui/component.hpp"
#include "procgen/noisemap.hpp"
#include <cstdint>
#include <memory>

class DebugWin : public Component
{
public:
  DebugWin(std::shared_ptr<NoiseMap> nm);

  void render(FrameBuffer<uint32_t> fb, Camera camera, long delta);
  void update(long delta);

  std::shared_ptr<NoiseMap> nm;

  bool fbm_selected = true;
};
