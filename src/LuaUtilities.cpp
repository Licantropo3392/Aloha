#include <LuaUtilities.hpp>

bool CheckLua(lua_State *L, int result)
{
    if (result != LUA_OK)
    {
        std::cerr << "Lua Error: " << lua_tostring(L, -1) << std::endl;
        lua_pop(L, 1); // Remove error message from stack
        return false;
    }

    return true;
}