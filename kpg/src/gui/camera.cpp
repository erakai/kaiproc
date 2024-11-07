#include "gui/camera.hpp"
#include "SDL_events.h"
#include "gui/input.hpp"

Camera::Camera(int w, int h, int initial_pixel_size) : w(w), h(h)
{
  set_pixel_size(initial_pixel_size);

  std::function<void(int t, int b, int x, int y, int mw)> input =
      [this](int t, int b, int x, int y, int mw)
  { mouse_input(t, b, x, y, mw); };
  input::mouse_callbacks.push_back(input);
}

bool Camera::project(int &x, int &y)
{
  x -= cam_x;
  y -= cam_y;

  x *= pixel_size;
  y *= pixel_size;

  if (x >= w || x < 0)
    return false;
  if (y >= h || y < 0)
    return false;

  return true;
}

bool Camera::unproject(int &x, int &y)
{
  if (x >= w || x < 0)
    return false;
  if (y >= h || y < 0)
    return false;

  x /= pixel_size;
  y /= pixel_size;

  x += cam_x;
  y += cam_y;

  return true;
}

bool Camera::zoom(int mx, int my, float zoom_delta)
{
  // The mouse y coord is inverse our world coords
  my = h - my;

  float nz = zoom_level + zoom_delta;

  if (nz < min_zoom)
    nz = min_zoom;
  if (nz > max_zoom)
    nz = max_zoom;
  if (nz == zoom_level)
    return false;

  // Sigmoid function so zooming feels natural
  // Will always be in [0, 1]
  float new_effective_zoom = ((exp(nz) / (1 + exp(nz))) - 0.5) * 2;

  // Re-calculate pixel size
  int new_pixel_size = new_effective_zoom * max_pixel_size + 1;

  // Update world pos to "zoom into" x and y
  if ((int) new_pixel_size != pixel_size)
  {
    // First grab the world coordinates of our mouse
    int m_world_x = mx;
    int m_world_y = my;
    unproject(m_world_x, m_world_y);

    // Now calculate the new world coordinate of the mouse
    pixel_size = new_pixel_size;
    int new_m_world_x = mx;
    int new_m_world_y = my;
    unproject(new_m_world_x, new_m_world_y);

    // Offset so the mouse's world coodinate doesn't change
    cam_x += (m_world_x - new_m_world_x);
    cam_y += (m_world_y - new_m_world_y);
  }

  // Update zoom fields
  zoom_level = nz;
  pixel_size = new_pixel_size;

  return true;
}

void Camera::set_pixel_size(int nps)
{
  if (nps > max_pixel_size || nps < 0)
    return;
  if (nps == pixel_size)
    return;

  float effective_zoom = (nps - 1) / (float) max_pixel_size;
  effective_zoom /= 2;
  effective_zoom += 0.5;
  float new_zoom_level = log(effective_zoom / (1 - effective_zoom)) + 0.01;

  zoom(w / 2, h / 2, new_zoom_level - zoom_level);
}

void Camera::set_max_pixel_size(int new_max)
{
  max_pixel_size = new_max;
  max_zoom = 0.5f * new_max;
  if (pixel_size > max_pixel_size)
    pixel_size = max_pixel_size;
  set_pixel_size(pixel_size);
}

void Camera::mouse_input(int type, int button, int x, int y, int mw)
{
  // Zooming behavior
  // Panning behavior
  if (type == SDL_MOUSEBUTTONDOWN && button == SDL_BUTTON_LEFT)
  {
    pressed = true;
  }
  if (type == SDL_MOUSEBUTTONDOWN && button == SDL_BUTTON_LEFT)
  {
    pressed = true;
  }
  if (type == SDL_MOUSEMOTION)
  {
    if (pressed && button == SDL_BUTTON_LEFT)
    {
      float x_delta = (x - mouse_x) / (float) pixel_size;
      float y_delta = (y - mouse_y) / (float) pixel_size;
      cam_x -= x_delta;
      cam_y += y_delta;
    }

    mouse_x = x;
    mouse_y = y;
  }

  if (type == SDL_MOUSEWHEEL)
  {
    if (mw > 0)
    {
      zoom(mouse_x, mouse_y, 0.15);
    }
    else if (mw < 0)
    {
      zoom(mouse_x, mouse_y, -0.15);
    }
  }
}
