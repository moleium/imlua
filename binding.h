//===-- binding.h - few ImGui bindings for Lua -------------------===//

#ifndef BINDING_H
#define BINDING_H

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

int l_ImGui_Begin(lua_State* L);
int l_ImGui_End(lua_State* L);

int l_ImGui_SetNextWindowPos(lua_State* L);
int l_ImGui_SetNextWindowSize(lua_State* L);

int l_ImGui_Text(lua_State* L);
int l_ImGui_Button(lua_State* L);

int l_ImGui_InputText(lua_State* L);
int l_ImGui_SliderFloat(lua_State* L);
int l_ImGui_Checkbox(lua_State* L);
int l_ImGui_RadioButton(lua_State* L);

int l_ImGui_GetIO(lua_State* L);

void register_imgui_bindings(lua_State* L);

#endif // BINDING_H