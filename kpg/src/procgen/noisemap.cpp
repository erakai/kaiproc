#include "procgen/noisemap.hpp"
#include "gui/color.hpp"
#include "procgen/perlin.hpp"

NoiseMap::NoiseMap(int w, int h) : map(w, h)
{
  generate_map();
}

void NoiseMap::generate_map()
{
  perlin::seed(seed);

  Color white = {255, 255, 255};
  for (int y = 0; y < map.h; y++)
  {
    for (int x = 0; x < map.w; x++)
    {
      double scalar = perlin::noise(x * frequency, y * frequency);
      Color col = white * scalar;

      map.set(y, x, color_to_int(col));
    }
  }
}

void NoiseMap::render(FrameBuffer<uint32_t> fb, long delta)
{
  // generate_map();
  for (int y = 0; y < fb.h; y++)
  {
    for (int x = 0; x < fb.w; x++)
    {
      fb.set(y, x, map.get(y, x));
    }
  }
}

void NoiseMap::update(long delta)
{
}
