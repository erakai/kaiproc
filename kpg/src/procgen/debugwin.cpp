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
  ImGui::SetNextWindowPos({870, 10}, ImGuiCond_Once);
  ImGui::SetNextWindowSize({400, 365}, ImGuiCond_Once);

  ImGui::Begin("Debug");
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
  if (ImGui::Button("Generate"))
  {
    if (fbm_selected)
      nm->generate_map_fbm();
    else
      nm->generate_map_perlin();
  }
  ImGui::SameLine();
  if (ImGui::Button("Generate++"))
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
  ImGui::End();
}

void DebugWin::update(long delta)
{
}
