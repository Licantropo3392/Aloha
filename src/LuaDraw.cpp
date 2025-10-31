#include <lua.hpp>

#ifdef __3DS__
#include <3ds.h>
#include <citro2d.h>

int LuaInit(lua_State *L)
{
    return 0;
}

int LuaSetFPS(lua_State *L)
{
    return 0;
}

int LuaClose(lua_State *L)
{
    C2D_Fini();
    C3D_Fini();

    gfxExit();
    return 0;
}

void DeltaTime(u64 *oldTime, double *deltaTime)
{
    u64 currentTime = osGetTime();

    *deltaTime = (double)((currentTime - *oldTime) / 1000.0);
    *oldTime = currentTime;
}

int LuaRectangle(lua_State *L)
{
    float x = luaL_checknumber(L, 1);
    float y = luaL_checknumber(L, 2);
    float width = luaL_checknumber(L, 3);
    float height = luaL_checknumber(L, 4);

    int R = 255;
    int G = 255;
    int B = 255;
    int A = 255;

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

    u32 color = C2D_Color32(R, G, B, A);

    C2D_DrawRectangle(x, y, 0, width, height, color, color, color, color);
    return 0;
}

int LuaCircle(lua_State *L)
{
    float x = luaL_checknumber(L, 1);
    float y = luaL_checknumber(L, 2);
    float radius = luaL_checknumber(L, 3);

    if (x <= 0 || y <= 0 || radius <= 0)
        return 0;

    int R = 255;
    int G = 255;
    int B = 255;
    int A = 255;

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

    u32 color = C2D_Color32(R, G, B, A);

    C2D_DrawCircle(x, y, 0, radius, color, color, color, color);
    return 0;
}

#else
#include <raylib.h>

extern int targetFPS;

int LuaInit(lua_State *L)
{
    int screenWidth = luaL_checkinteger(L, 1);
    int screenHeight = luaL_checkinteger(L, 2);
    const char *title = luaL_checkstring(L, 3);

    // SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(screenWidth, screenHeight, title);

    return 0;
}

int LuaSetFPS(lua_State *L)
{
    targetFPS = luaL_checkinteger(L, 1);
    SetTargetFPS(targetFPS);
    return 0;
}

int LuaClose(lua_State *L)
{
    CloseWindow();
    return 0;
}

void DeltaTime(double *oldTime, double *deltaTime)
{
    double currentTime = GetTime();

    *deltaTime = currentTime - *oldTime;
    *oldTime = currentTime;
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
        R = luaL_checkinteger(L, -1);
        lua_pop(L, 1);

        lua_getfield(L, 5, "g");
        G = luaL_checkinteger(L, -1);
        lua_pop(L, 1);

        lua_getfield(L, 5, "b");
        B = luaL_checkinteger(L, -1);
        lua_pop(L, 1);

        lua_getfield(L, 5, "a");
        A = luaL_checkinteger(L, -1);
        lua_pop(L, 1);
    }

    Color color = {(unsigned char)R, (unsigned char)G, (unsigned char)B, (unsigned char)A};

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
        R = luaL_checkinteger(L, -1);
        lua_pop(L, 1);

        lua_getfield(L, 4, "g");
        G = luaL_checkinteger(L, -1);
        lua_pop(L, 1);

        lua_getfield(L, 4, "b");
        B = luaL_checkinteger(L, -1);
        lua_pop(L, 1);

        lua_getfield(L, 4, "a");
        A = luaL_checkinteger(L, -1);
        lua_pop(L, 1);
    }

    Color color = {(unsigned char)R, (unsigned char)G, (unsigned char)B, (unsigned char)A};

    DrawCircle(x, y, radius, color);
    return 0;
}

#endif
