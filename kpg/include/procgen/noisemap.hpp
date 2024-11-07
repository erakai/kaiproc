#pragma once

#include "gui/component.hpp"
#include "procgen/fbm.hpp"

class NoiseMap : public Component
{
public:
  NoiseMap(int w, int h);
  ~NoiseMap() { map.destroy(); }

  uint32_t scalar_to_color(float scalar);
  void generate_map_perlin();
  void generate_map_fbm();
  void render(FrameBuffer<uint32_t> fb, std::shared_ptr<Camera> camera,
              long delta);
  void update(long delta);

  FrameBuffer<uint32_t> map;
  int seed = 1;
  bool binary_colors = true;
  fbm::params params;
};
