#include "procgen/fbm.hpp"
#include "procgen/perlin.hpp"

namespace fbm
{

double gen(double x, double y, double z, params p)
{
  x *= p.frequency;
  y *= p.frequency;
  z *= p.frequency;

  double ret = 0;

  for (int i = 0; i < p.octaves; i++)
  {
    ret += (p.amplitude * perlin::noise(x, y, z));
    x *= 2;
    y *= 2;
    z *= 2;
    p.amplitude *= 0.5;
  }

  return ret;
}

double gen(double x, double y, params p)
{
  return gen(x, y, 1.0, p);
}

}; // namespace fbm
