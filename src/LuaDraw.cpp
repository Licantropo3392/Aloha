#include <LuaDraw.hpp>

#ifdef __3DS__

int LuaInit(lua_State *L)
{
    int screenWidth = luaL_checkinteger(L, 1);
    int screenHeight = luaL_checkinteger(L, 2);
    const char *title = luaL_checkstring(L, 3);

    InitWindow(screenWidth, screenHeight, title);
    SetTargetFPS(60);

    return 0;
}

int LuaSetFPS(lua_State *L)
{
    int fps = luaL_checkinteger(L, 1);
    SetTargetFPS(fps);
    return 0;
}

int LuaClose(lua_State *L)
{
    CloseWindow();
    return 0;
}

int LuaRectangle(lua_State *L)
{
    float x = luaL_checknumber(L, 1);
    float y = luaL_checknumber(L, 2);
    float width = luaL_checknumber(L, 3);
    float height = luaL_checknumber(L, 4);

    int R = WHITE.r;
    int G = WHITE.g;
    int B = WHITE.b;
    int A = WHITE.a;

    if (lua_istable(L, 5))
    {
        lua_getfield(L, 5, "r");
        R = lua_tointeger(L, -1);
        lua_pop(L, 1);

        lua_getfield(L, 5, "g");
        G = lua_tointeger(L, -1);
        lua_pop(L, 1);

        lua_getfield(L, 5, "b");
        B = lua_tointeger(L, -1);
        lua_pop(L, 1);

        lua_getfield(L, 5, "a");
        A = lua_tointeger(L, -1);
        lua_pop(L, 1);
    }

    Color color = { (unsigned char)R, (unsigned char)G, (unsigned char)B, (unsigned char)A };

    DrawRectangle(x, y, width, height, color);
    return 0;
}

int LuaCircle(lua_State *L)
{
    float x = luaL_checknumber(L, 1);
    float y = luaL_checknumber(L, 2);
    float radius = luaL_checknumber(L, 3);

    int R = WHITE.r;
    int G = WHITE.g;
    int B = WHITE.b;
    int A = WHITE.a;

    if (lua_istable(L, 4))
    {
        lua_getfield(L, 4, "r");
        R = lua_tointeger(L, -1);
        lua_pop(L, 1);

        lua_getfield(L, 4, "g");
        G = lua_tointeger(L, -1);
        lua_pop(L, 1);

        lua_getfield(L, 4, "b");
        B = lua_tointeger(L, -1);
        lua_pop(L, 1);

        lua_getfield(L, 4, "a");
        A = lua_tointeger(L, -1);
        lua_pop(L, 1);
    }

    Color color = { (unsigned char)R, (unsigned char)G, (unsigned char)B, (unsigned char)A };

    DrawCircle(x, y, radius, color);
    return 0;
}

#else

int LuaInit(lua_State *L)
{
    int screenWidth = luaL_checkinteger(L, 1);
    int screenHeight = luaL_checkinteger(L, 2);
    const char *title = luaL_checkstring(L, 3);

    InitWindow(screenWidth, screenHeight, title);
    SetTargetFPS(60);

    return 0;
}

int LuaSetFPS(lua_State *L)
{
    int fps = luaL_checkinteger(L, 1);
    SetTargetFPS(fps);
    return 0;
}

int LuaClose(lua_State *L)
{
    CloseWindow();
    return 0;
}

int LuaRectangle(lua_State *L)
{
    float x = luaL_checknumber(L, 1);
    float y = luaL_checknumber(L, 2);
    float width = luaL_checknumber(L, 3);
    float height = luaL_checknumber(L, 4);

    int R = WHITE.r;
    int G = WHITE.g;
    int B = WHITE.b;
    int A = WHITE.a;

    if (lua_istable(L, 5))
    {
        lua_getfield(L, 5, "r");
        R = lua_tointeger(L, -1);
        lua_pop(L, 1);

        lua_getfield(L, 5, "g");
        G = lua_tointeger(L, -1);
        lua_pop(L, 1);

        lua_getfield(L, 5, "b");
        B = lua_tointeger(L, -1);
        lua_pop(L, 1);

        lua_getfield(L, 5, "a");
        A = lua_tointeger(L, -1);
        lua_pop(L, 1);
    }

    Color color = { (unsigned char)R, (unsigned char)G, (unsigned char)B, (unsigned char)A };

    DrawRectangle(x, y, width, height, color);
    return 0;
}

int LuaCircle(lua_State *L)
{
    float x = luaL_checknumber(L, 1);
    float y = luaL_checknumber(L, 2);
    float radius = luaL_checknumber(L, 3);

    int R = WHITE.r;
    int G = WHITE.g;
    int B = WHITE.b;
    int A = WHITE.a;

    if (lua_istable(L, 4))
    {
        lua_getfield(L, 4, "r");
        R = lua_tointeger(L, -1);
        lua_pop(L, 1);

        lua_getfield(L, 4, "g");
        G = lua_tointeger(L, -1);
        lua_pop(L, 1);

        lua_getfield(L, 4, "b");
        B = lua_tointeger(L, -1);
        lua_pop(L, 1);

        lua_getfield(L, 4, "a");
        A = lua_tointeger(L, -1);
        lua_pop(L, 1);
    }

    Color color = { (unsigned char)R, (unsigned char)G, (unsigned char)B, (unsigned char)A };

    DrawCircle(x, y, radius, color);
    return 0;
}

#endif
