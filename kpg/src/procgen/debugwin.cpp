#include "procgen/debugwin.hpp"

#include "gui/gui.hpp"
#include "imgui.h"
#include "procgen/noisemap.hpp"

using namespace std;

DebugWin::DebugWin(shared_ptr<NoiseMap> nm) : nm(nm)
{
}

void DebugWin::render(FrameBuffer<uint32_t> fb, long delta)
{
  ImGui::SetNextWindowPos({870, 10}, ImGuiCond_Once);
  ImGui::SetNextWindowSize({400, 260}, ImGuiCond_Once);

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
  ImGui::Text("Frequency");
  ImGui::SliderFloat("##freq", &nm->frequency, 0.001, 1);
  ImGui::Spacing();
  if (ImGui::Button("Generate"))
    nm->generate_map();
  ImGui::SameLine();
  if (ImGui::Button("Generate++"))
  {
    nm->generate_map();
    nm->seed++;
  }
  ImGui::NewLine();
  ImGui::SetWindowFontScale(1.2);
  ImGui::End();
}

void DebugWin::update(long delta)
{
}
