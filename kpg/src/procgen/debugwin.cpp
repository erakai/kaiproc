#include "procgen/debugwin.hpp"

#include "gui/gui.hpp"
#include "imgui.h"
#include "procgen/noisemap.hpp"

using namespace std;

DebugWin::DebugWin(shared_ptr<NoiseMap> nm) : nm(nm)
{
}

void DebugWin::render(FrameBuffer<uint32_t> fb, Camera camera, long delta)
{
  // =========================================== Generation

  ImGui::SetNextWindowPos({10, 10}, ImGuiCond_Once);
  ImGui::SetNextWindowSize({350, 360}, ImGuiCond_Once);
  ImGui::Begin("Generation");
  ImGui::Text("ImGUI: %.3f ms/frame (%.1f FPS)",
              1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
  ImGui::Text("Recorded: %.0f ms/frame (%.1d FPS)", frametime,
              frames_per_second);
  ImGui::Spacing();
  ImGui::Text("Max FPS");
  ImGui::SliderInt("##fps", &FPS, -1, 500);
  ImGui::Spacing();
  ImGui::Text("Seed");
  ImGui::SliderInt("##seed", &nm->seed, -1, 500);
  ImGui::Text("Frequency (Zoom)");
  ImGui::SliderFloat("##freq", &nm->params.frequency, 0.5, 0.001);
  ImGui::Text("Octaves (Detail)");
  ImGui::SliderInt("##oct", &nm->params.octaves, 1, 25);
  ImGui::Text("Amplitude (Contrast)");
  ImGui::SliderFloat("##amp", &nm->params.amplitude, 0.35, 0.9);
  ImGui::Spacing();
  if (ImGui::Button("Reload"))
  {
    if (fbm_selected)
      nm->generate_map_fbm();
    else
      nm->generate_map_perlin();
  }
  ImGui::SameLine();
  if (ImGui::Button("Generate"))
  {
    nm->seed++;
    if (fbm_selected)
      nm->generate_map_fbm();
    else
      nm->generate_map_perlin();
  }
  ImGui::Checkbox("Enable FBM", &fbm_selected);
  ImGui::SameLine();
  ImGui::Checkbox("Binary Colors", &nm->binary_colors);
  ImGui::SetWindowFontScale(1.2);
  ImVec2 pos = ImGui::GetWindowPos();
  ImVec2 size = ImGui::GetWindowSize();
  ImGui::End();

  // =========================================== Camera

  ImGui::SetNextWindowPos({pos.x, pos.y + size.y});
  ImGui::SetNextWindowSize({size.x, 160}, ImGuiCond_Once);
  ImGui::Begin("Camera");
  ImGui::Text("Pixel Size: %d", camera.pixel_size);
  float current = camera.pixel_size;
  float new_value = current;
  ImGui::SliderFloat("##pixel", &new_value, 1, camera.max_pixel_size);
  if (current != new_value)
  {
    camera.set_pixel_size(new_value);
  }
  ImGui::Text("Zoom level: %f", camera.zoom_level);
  ImGui::Text("Camera Pos: (%f, %f)", camera.cam_x, camera.cam_y);
  ImGui::Text("Mouse Pos: (%d, %d)", camera.mouse_x, camera.mouse_y);
  ImGui::Text("Mouse World Pos: (%d, %d)",
              (camera.mouse_x / camera.pixel_size) + (int) camera.cam_x,
              (camera.mouse_y / camera.pixel_size) + (int) camera.cam_y);
  ImGui::SetWindowFontScale(1.2);
  ImGui::End();
}

void DebugWin::update(long delta)
{
}
