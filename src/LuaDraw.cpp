#include <lua.hpp>

#ifdef __3DS__
#include <3ds.h>
#include <citro2d.h>
#else
#include <raylib.h>
#endif

extern int targetFPS;

#ifdef __3DS__
void DeltaTime(u64 *oldTime, double *deltaTime)
{
    u64 currentTime = osGetTime();

    *deltaTime = (double)((currentTime - *oldTime) / 1000.0);
    *oldTime = currentTime;
}
#endif

int LuaInit(lua_State *L)
{
    #ifndef __3DS__
    int screenWidth = luaL_checkinteger(L, 1);
    int screenHeight = luaL_checkinteger(L, 2);
    const char *title = luaL_checkstring(L, 3);

    // SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(screenWidth, screenHeight, title);
    #endif

    return 0;
}

int LuaSetFPS(lua_State *L)
{
    #ifndef __3DS__
    targetFPS = luaL_checkinteger(L, 1);
    SetTargetFPS(targetFPS);
    #endif

    return 0;
}

int LuaClose(lua_State *L)
{
    #ifdef __3DS__
    C2D_Fini();
    C3D_Fini();
    gfxExit();
    #else
    CloseWindow();
    #endif

    return 0;
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

    #ifdef __3DS__
    u32 color = C2D_Color32(R, G, B, A);
    C2D_DrawRectangle(x, y, 0, width, height, color, color, color, color);
    #else
    Color color = {(unsigned char)R, (unsigned char)G, (unsigned char)B, (unsigned char)A};
    DrawRectangle(x, y, width, height, color);
    #endif

    return 0;
}

int LuaCircle(lua_State *L)
{
    float x = luaL_checknumber(L, 1);
    float y = luaL_checknumber(L, 2);
    float radius = luaL_checknumber(L, 3);

    int R = 255;
    int G = 255;
    int B = 255;
    int A = 255;

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

    #ifdef __3DS__
    u32 color = C2D_Color32(R, G, B, A);
    C2D_DrawCircle(x, y, 0, radius, color, color, color, color);
    #else
    Color color = {(unsigned char)R, (unsigned char)G, (unsigned char)B, (unsigned char)A};
    DrawCircle(x, y, radius, color);
    #endif

    return 0;
}
