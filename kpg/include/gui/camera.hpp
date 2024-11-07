#pragma once

class Camera
{
public:
  Camera(int w, int h, int initial_pixel_size = 2);

  // Returns true if on screen
  // x and y will correspond to the top-left corner of the rectangle of
  // side length pixel_size - so if (0, 0) is returned and pixel_length
  // is 5, the calling function should render the (0, 0) to (5, 5) rect
  bool project(int &x, int &y);

  // Returns true if valid input
  // Converts from display to world
  bool unproject(int &x, int &y);

  // Returns true if successful
  bool zoom(int x, int y, float zoom_delta);

  // Sets the current pixel_size
  void set_pixel_size(int nps);
  void set_max_pixel_size(int new_max);

  float cam_x = 0;
  float cam_y = 0;

  /*
  This is the side length of the rectangle (in display pixels) that one
  world coordinate maps to. So if this is 5 and the pixel at (0, 0) is black,
  the camera should project anything between (0, 0) and (5, 5) as black.
  */
  int pixel_size = 1;
  float max_pixel_size = 10;

  // Used to smoothly transition between discrete pixel_size values
  float zoom_level = 0;
  const float min_zoom = 0; // arbitrary value
  float max_zoom = 5;       // arbitrary value

  // display width, height
  int w, h;

  // save mouse pos for camera dragging
  void mouse_input(int type, int button, int x, int y, int mw);
  bool pressed = false;
  int mouse_x, mouse_y;
};
