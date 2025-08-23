#include <iostream>
#include <LuaUtilities.hpp>
#include <LuaDraw.hpp>

int main()
{
    int screenWidth = 800;
    int screenHeight = 450;
    std::string title = "Aloha2D";

    lua_State *L = luaL_newstate();

    luaL_openlibs(L);
    lua_register(L, "InitWindow", LuaInit);
    lua_register(L, "SetTargetFPS", LuaSetFPS);

    lua_register(L, "CloseWindow", LuaClose);

    lua_register(L, "DrawRectangle", LuaRectangle);
    lua_register(L, "DrawCircle", LuaCircle);

    if (CheckLua(L, luaL_dofile(L, "../src/lua/main.lua")))
    {
        lua_getglobal(L, "Init");

        if (lua_isfunction(L, -1))
        {
            CheckLua(L, lua_pcall(L, 0, 0, 0));
        }
    }

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (CheckLua(L, luaL_dofile(L, "../src/lua/main.lua")))
        {
            lua_getglobal(L, "Update");

            if (lua_isfunction(L, -1))
            {
                CheckLua(L, lua_pcall(L, 0, 0, 0));
            }
        }

        EndDrawing();
    }

    if (CheckLua(L, luaL_dofile(L, "../src/lua/main.lua")))
    {
        lua_getglobal(L, "Unload");

        if (lua_isfunction(L, -1))
        {
            CheckLua(L, lua_pcall(L, 0, 0, 0));
        }
    }

    lua_close(L);

    return 0;
}