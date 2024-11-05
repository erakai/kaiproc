#include "gui/gui.hpp"

#include "SDL.h"

#include "procgen/noisemap.hpp"
#include <memory>

using namespace std;

int main(int argc, char **argv)
{
  GUI gui(1280, 640);

  shared_ptr<NoiseMap> nm = shared_ptr<NoiseMap>(new NoiseMap(1280, 640));
  gui.add_component(nm);

  gui.run();

  return 0;
}
