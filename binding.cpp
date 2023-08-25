//===-- binding.cpp - few ImGui bindings for Lua -------------------===//

#include "binding.h"
#include <imgui/imgui.h>
#include <vector>

ImVec2 lua_toImVec2(lua_State* L, int idx) {
    ImVec2 v;
    lua_pushstring(L, "x");
    lua_gettable(L, idx);
    v.x = luaL_checknumber(L, -1);
    lua_pop(L, 1);

    lua_pushstring(L, "y");
    lua_gettable(L, idx);
    v.y = luaL_checknumber(L, -1);
    lua_pop(L, 1);

    return v;
}

// push ImVec2 to stack
void lua_pushImVec2(lua_State* L, const ImVec2& v) {
    lua_newtable(L);
    lua_pushstring(L, "x");
    lua_pushnumber(L, v.x);
    lua_settable(L, -3);

    lua_pushstring(L, "y");
    lua_pushnumber(L, v.y);
    lua_settable(L, -3);
}

int l_ImGui_Begin(lua_State* L) {
    const char* name = luaL_checkstring(L, 1);
    bool* p_open = nullptr;
    if (!lua_isnoneornil(L, 2)) {
        p_open = (bool*)lua_touserdata(L, 2);
    }
    ImGuiWindowFlags flags = luaL_optinteger(L, 3, 0);

    bool result = ImGui::Begin(name, p_open, flags);

    lua_newtable(L);

    lua_pushstring(L, "End");
    lua_pushcfunction(L, l_ImGui_End);
    lua_settable(L, -3);

    return 1;
}

int l_ImGui_End(lua_State* L) {
    ImGui::End();
    return 0;
}

int l_ImGui_SetNextWindowPos(lua_State* L) {
    ImVec2 pos = lua_toImVec2(L, 1);
    int cond = luaL_optinteger(L, 2, 0);
    ImVec2 pivot = lua_toImVec2(L, 3);

    ImGui::SetNextWindowPos(pos, cond, pivot);
    return 0;
}

int l_ImGui_SetNextWindowSize(lua_State* L) {
    ImVec2 size = lua_toImVec2(L, 1);
    int cond = luaL_optinteger(L, 2, 0);

    ImGui::SetNextWindowSize(size, cond);
    return 0;
}

int l_ImGui_Text(lua_State* L) {
	const char* text = luaL_checkstring(L, 1);
	ImGui::Text("%s", text);
	return 0;
}

int l_ImGui_Button(lua_State* L) {
	const char* label = luaL_checkstring(L, 1);
	bool result = ImGui::Button(label);
	lua_pushboolean(L, result);
	return 1;
}

int l_ImGui_InputText(lua_State* L) {
    const char* label = luaL_checkstring(L, 1);
    char* buf = (char*)luaL_checkstring(L, 2);
    size_t buf_size = luaL_checkinteger(L, 3);
    ImGuiInputTextFlags flags = luaL_optinteger(L, 4, 0);
    bool result = ImGui::InputText(label, buf, buf_size, flags);
    lua_pushboolean(L, result);
    return 1;
}

int l_ImGui_SliderFloat(lua_State* L) {
    const char* label = luaL_checkstring(L, 1);
    float v = luaL_checknumber(L, 2);
    float v_min = luaL_checknumber(L, 3);
    float v_max = luaL_checknumber(L, 4);
    const char* format = luaL_optstring(L, 5, "%.3f");
    ImGuiSliderFlags flags = luaL_optinteger(L, 6, 0);
    bool result = ImGui::SliderFloat(label, &v, v_min, v_max, format, flags);
    lua_pushboolean(L, result);
    lua_pushnumber(L, v);
    return 2;
}

int l_ImGui_Checkbox(lua_State* L) {
    const char* label = luaL_checkstring(L, 1);
    bool v = lua_toboolean(L, 2);
    bool result = ImGui::Checkbox(label, &v);
    lua_pushboolean(L, result);
    lua_pushboolean(L, v);
    return 2;
}

int l_ImGui_RadioButton(lua_State* L) {
    const char* label = luaL_checkstring(L, 1);
    bool active = lua_toboolean(L, 2);
    bool result = ImGui::RadioButton(label, active);
    lua_pushboolean(L, result);
    return 1;
}

int l_ImGui_GetIO(lua_State* L) {
    ImGuiIO& io = ImGui::GetIO();

    lua_newtable(L);

    lua_pushstring(L, "DisplaySize");
    lua_pushImVec2(L, io.DisplaySize);
    lua_settable(L, -3);

    return 1;
}

void register_imgui_bindings(lua_State* L) {
    lua_newtable(L);

#define REGISTER_LUA_FUNC(name) \
	lua_pushstring(L,#name); \
	lua_pushcfunction(L,l_ImGui_##name); \
	lua_settable(L,-3)

    REGISTER_LUA_FUNC(Begin);
    REGISTER_LUA_FUNC(End);
    REGISTER_LUA_FUNC(SetNextWindowPos);
    REGISTER_LUA_FUNC(SetNextWindowSize);
    REGISTER_LUA_FUNC(Text);
    REGISTER_LUA_FUNC(Button);
    REGISTER_LUA_FUNC(GetIO);
    REGISTER_LUA_FUNC(InputText);
    REGISTER_LUA_FUNC(SliderFloat);
    REGISTER_LUA_FUNC(Checkbox);
    REGISTER_LUA_FUNC(RadioButton);

#undef REGISTER_LUA_FUNC

    lua_setglobal(L, "ImGui");
}