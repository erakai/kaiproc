#pragma once

#include "gui/component.hpp"
#include "gui/display.hpp"

#include <chrono>
#include <vector>

using namespace std;

extern int FPS;
extern int frames_per_second;
extern float frametime;

class GUI
{
public:
  GUI(int w, int h);

  void run(void);
  void update(long delta);
  void render(long delta);
  void close();

  void add_component(std::shared_ptr<Component> comp);

  int fps();
  Display &get_display();

private:
  // Controls game loop
  bool running;

  // Last and current frame time
  chrono::system_clock::time_point a;
  chrono::system_clock::time_point b;

  // Control actually rendering and display
  std::shared_ptr<Camera> camera;
  Display display;

  // All top level components to render and update
  std::vector<std::shared_ptr<Component>> components;

  // Frames per second
  long ms_counter = 0;
  int frames_in_last_second = 0;
};
