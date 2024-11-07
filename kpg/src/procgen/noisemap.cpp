#include "procgen/noisemap.hpp"
#include "gui/color.hpp"
#include "procgen/perlin.hpp"

NoiseMap::NoiseMap(int w, int h) : map(w, h)
{
  generate_map_fbm();
}

uint32_t NoiseMap::scalar_to_color(float scalar)
{
  if (!binary_colors)
    return (color_to_int(cwhite * (1 - scalar)));

  if (scalar > 0.51)
    return color_to_int(cgreen);
  if (scalar > 0.49)
    return color_to_int(cblack);
  return color_to_int(cblue);
}

void NoiseMap::generate_map_perlin()
{
  perlin::seed(seed);

  for (int y = 0; y < map.h; y++)
  {
    for (int x = 0; x < map.w; x++)
    {
      double scalar = perlin::noise(x * params.frequency, y * params.frequency);
      map.set(y, x, scalar_to_color(scalar));
    }
  }
}

void NoiseMap::generate_map_fbm()
{
  perlin::seed(seed);

  for (int y = 0; y < map.h; y++)
  {
    for (int x = 0; x < map.w; x++)
    {
      double scalar =
          fbm::gen(x * params.frequency, y * params.frequency, params);

      map.set(y, x, scalar_to_color(scalar));
    }
  }
}

void NoiseMap::render(FrameBuffer<uint32_t> fb, std::shared_ptr<Camera> camera,
                      long delta)
{
  for (int y = 0; y < map.h; y++)
  {
    for (int x = 0; x < map.w; x++)
    {
      int nx = x;
      int ny = y;
      if (!camera->project(nx, ny))
        continue;

      fb.raster_rect(nx, ny, camera->pixel_size, camera->pixel_size,
                     map.get(y, x));
    }
  }
}

void NoiseMap::update(long delta)
{
}
