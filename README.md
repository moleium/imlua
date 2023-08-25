# imlua

Few ImGui bindings to lua

## Usage

```cpp
lua_State* L = luaL_newstate();
register_imgui_bindings(L);
```

```lua
local window = ImGui.Begin("Demo")

local buffer = "Femboys are hot"
local buffer_size = 256

ImGui.Text("Hello from lua")
ImGui.InputText("##input", buffer, buffer_size)

if ImGui.Button("Click me") then
    print("Clicked")
end

window.End()
```
