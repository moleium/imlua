#include "bindings.h"
#include "imgui.h"

namespace ImGuiBindings {
void bindImGui(sol::state &lua) {
  lua["ImGui"] = lua.create_table();

  lua["ImGui"]["BeginWindow"] = [](const char *name) {
    return ImGui::Begin(name);
  };

  lua["ImGui"]["EndWindow"] = []() { ImGui::End(); };

  lua["ImGui"]["Text"] = [](const char *text) {
    ImGui::Text("%s", text);
  };

  lua["ImGui"]["Button"] = [](const char *label) {
    return ImGui::Button(label);
  };
}
} // namespace ImGuiBindings
