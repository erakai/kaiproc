#pragma once

#include "gui/display.hpp"

#include <chrono>

using namespace std;

extern int FPS;

class GUI
{
public:
  GUI();

  void run(void);
  void update(long delta);
  void render(long delta);
  void close();

  int fps();
  Display &get_display();

private:
  // Controls game loop
  bool running;

  // Last and current frame time
  chrono::system_clock::time_point a;
  chrono::system_clock::time_point b;

  // Control actually rendering and display
  Display display;

  // Frames per second
  int frames_per_second = 0;
  float frametime = 0;
  long ms_counter = 0;
  int frames_in_last_second = 0;
};
