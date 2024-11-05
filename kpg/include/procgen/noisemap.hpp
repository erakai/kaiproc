#pragma once

#include "gui/component.hpp"

class NoiseMap : public Component
{
public:
  NoiseMap(int w, int h);
  ~NoiseMap() { map.destroy(); }

  void generate_map();
  void render(FrameBuffer<uint32_t> fb, long delta);
  void update(long delta);

  FrameBuffer<uint32_t> map;
  int seed = 1;
  float frequency = 0.01;
};
