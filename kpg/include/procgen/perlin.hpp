#pragma once

#include <vector>

/*
This is an implementation of the improved perlin noise algorithm described by
Ken Perlin in 2002.

His paper can be found: https://mrl.cs.nyu.edu/~perlin/paper445.pdf
The reference java implementation: https://mrl.cs.nyu.edu/~perlin/noise/
*/
namespace perlin
{

/*
The only pseudo-random component, a duplicated permutation of ints in [0, 255]
that gradients are chosen from.
*/
extern std::vector<int> p;

/*
Seeds the permutation vector by shuffling it, using p\_seed. Should be called
before every new use. If p\_seed is -1, will use the reference permutation given
in the paper.
*/
void seed(int p_seed = -1);

/*
Returns a 3D noise value in [0, 1]. Call seed() first.
*/
double noise(double x, double y, double z);

/*
Returns a 2D noise value in [0, 1]. Call seed() first.
*/
double noise(double x, double y);

/*
Returns a 1D noise value in [0, 1]. Call seed() first.
*/
double noise(double x);

// Computes fade curves for the value
double fade(double t);
// Linear interpolation between a and b at step t
double lerp(double t, double a, double b);
// Grab gradients of cube
double grad(int hash, double x, double y, double z);

} // namespace perlin
