#pragma once

class Camera
{
public:
  Camera(int w, int h);

  // Returns true if on screen
  bool project(int &x, int &y);

  int cam_x = 0;
  int cam_y = 0;

  // display width, height
  int w, h;

  // save mouse pos for camera dragging
  void mouse_input(int type, int button, int x, int y);
  bool pressed = false;
  int mouse_x, mouse_y;
};
