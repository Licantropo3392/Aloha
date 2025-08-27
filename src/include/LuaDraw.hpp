#pragma once

#include <LuaUtilities.hpp>

#ifdef __3DS__
#include <3ds.h>
void DeltaTime(u64 *oldTime, double *deltaTime);
#else
#include <raylib.h>
#endif

int LuaInit(lua_State *L);

int LuaSetFPS(lua_State *L);

int LuaClose(lua_State *L);

void DeltaTime(double *oldTime, double *deltaTime);

int LuaRectangle(lua_State *L);

int LuaCircle(lua_State *L);