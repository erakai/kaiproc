#pragma once

/*
Implementation of fractal brownian motion:
  https://thebookofshaders.com/13/
*/
namespace fbm
{

struct params
{
  // Adds more detail
  int octaves = 6;
  // Adds more contract
  float amplitude = 0.5;
  // Zooms in
  float frequency = 0.15;
};

double gen(double x, double y, double z, params p);
double gen(double x, double y, params p);

}; // namespace fbm
