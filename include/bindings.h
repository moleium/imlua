#ifndef BINDINGS_H
#define BINDINGS_H

#include <sol/sol.hpp>
#include <array>

namespace ImGuiBindings {
void bindImGui(sol::state &lua);
}

#endif // BINDINGS_H