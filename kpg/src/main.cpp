#include "gui/gui.hpp"

#include "SDL.h"

#include "procgen/debugwin.hpp"
#include "procgen/noisemap.hpp"
#include <memory>

using namespace std;

#define WIDTH 1280
#define HEIGHT 720

int main(int argc, char **argv)
{
  GUI gui(WIDTH, HEIGHT);

  shared_ptr<NoiseMap> nm = shared_ptr<NoiseMap>(new NoiseMap(WIDTH, HEIGHT));
  gui.add_component(nm);

  shared_ptr<DebugWin> db = shared_ptr<DebugWin>(new DebugWin(nm));
  gui.add_component(db);

  gui.run();

  return 0;
}
