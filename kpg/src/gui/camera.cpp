#include "gui/camera.hpp"
#include "SDL_events.h"
#include "SDL_keycode.h"
#include "gui/input.hpp"

Camera::Camera(int w, int h) : w(w), h(h)
{
  cam_x = 0;
  cam_y = 0;

  std::function<void(int t, int b, int x, int y)> input =
      [this](int t, int b, int x, int y) { mouse_input(t, b, x, y); };
  input::mouse_callbacks.push_back(input);
}

bool Camera::project(int &x, int &y)
{
  x -= cam_x;
  y -= cam_y;

  if (x >= w || x < 0)
    return false;
  if (y >= h || y < 0)
    return false;

  return true;
}

void Camera::mouse_input(int type, int button, int x, int y)
{
  if (type == SDL_MOUSEBUTTONDOWN && button == SDL_BUTTON_LEFT)
  {
    pressed = true;
  }
  if (type == SDL_MOUSEBUTTONDOWN && button == SDL_BUTTON_LEFT)
  {
    pressed = true;
  }
  if (type == SDL_MOUSEMOTION && pressed && button == SDL_BUTTON_LEFT)
  {
    int x_delta = x - mouse_x;
    int y_delta = y - mouse_y;
    cam_x -= x_delta;
    cam_y += y_delta;
  }

  mouse_x = x;
  mouse_y = y;
}
