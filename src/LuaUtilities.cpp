#include <LuaUtilities.hpp>

bool CheckLua(lua_State *L, int result)
{
    if (result != 0)
    {
        std::cerr << "Lua Error: " << lua_tostring(L, -1) << std::endl;
        lua_pop(L, 1);
        return false;
    }

    return true;
}