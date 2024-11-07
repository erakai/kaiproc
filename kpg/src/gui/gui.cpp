#include "gui/gui.hpp"
#include "gui/input.hpp"
#include "utils/logger.hpp"

#include <thread>

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

int FPS = 120;
int frames_per_second = 0;
float frametime = 0;

GUI::GUI(int w, int h) : display(w, h, "KaiProc")
{
  camera = std::shared_ptr<Camera>(new Camera(w, h));
}

void GUI::run(void)
{
  if (!display.is_initialized())
  {
    log("Cannot run game - display not initialized.", ll::CRITICAL);
    close();
    return;
  }

  a = std::chrono::system_clock::now();
  b = std::chrono::system_clock::now();

  log("Beginning game loop...", ll::NOTE);
  running = true;
  while (running)
  {
    // Calculate how long we need to sleep for
    a = std::chrono::system_clock::now();
    std::chrono::duration<double, std::milli> work_time = a - b;

    float ms_per_frame = (1000.0f / FPS);
    if (work_time.count() < ms_per_frame)
    {
      std::chrono::duration<double, std::milli> delta_ms(ms_per_frame -
                                                         work_time.count());
      auto delta_ms_duration =
          std::chrono::duration_cast<std::chrono::milliseconds>(delta_ms);
      std::this_thread::sleep_for(
          std::chrono::milliseconds(delta_ms_duration.count()));
    }

    b = std::chrono::system_clock::now();
    std::chrono::duration<double, std::milli> sleep_time = b - a;

    long delta = (work_time + sleep_time).count();

    // Track stats about frames per second
    frametime = delta;
    ms_counter += delta;
    frames_in_last_second += 1;
    if (ms_counter >= 1000)
    {
      ms_counter = ms_counter - 1000;
      frames_per_second = frames_in_last_second;
      frames_in_last_second = 0;
    }

    running = input::poll_event_loop();

    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    update(delta);
    render(delta);
  }

  close();
}

void GUI::close()
{
  log("Shutting down...", ll::NOTE);
  display.close();
}

void GUI::update(long delta)
{
  for (auto comp : components)
    comp->update(delta);
}

void GUI::render(long delta)
{
  display.render(components, camera, delta);
}

void GUI::add_component(std::shared_ptr<Component> comp)
{
  components.push_back(comp);
}

int GUI::fps()
{
  return frames_per_second;
}

Display &GUI::get_display()
{
  return display;
}
