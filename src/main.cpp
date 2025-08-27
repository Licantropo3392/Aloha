#include <LuaUtilities.hpp>
#include <LuaDraw.hpp>

#ifdef __CONSOLE__
#include <citro2d.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <3ds.h>

int main()
{
    gfxInitDefault();
    consoleInit(GFX_BOTTOM, NULL);

    const u32 clrBackground = C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF);

    u64 oldTime = 0;
    double deltaTime;

    Result rc = romfsInit();
    if (rc)
        printf("romfsInit: %08lX\n", rc);
    else
    {
        lua_State *L = luaL_newstate();

        luaL_openlibs(L);
        lua_register(L, "InitWindow", LuaInit);
        lua_register(L, "SetTargetFPS", LuaSetFPS);

        lua_register(L, "CloseWindow", LuaClose);

        lua_register(L, "DrawRectangle", LuaRectangle);
        lua_register(L, "DrawCircle", LuaCircle);

        if (CheckLua(L, luaL_dofile(L, "romfs:/lua/main.lua")))
        {
            lua_getglobal(L, "Init");

            if (lua_isfunction(L, -1))
            {
                CheckLua(L, lua_pcall(L, 0, 0, 0));
            }
        }

        C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
        C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
        C2D_Prepare();

        C3D_RenderTarget *top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
        // C3D_RenderTarget *bottom = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);

        while (aptMainLoop())
        {
            // gspWaitForVBlank();

            DeltaTime(&oldTime, &deltaTime); // Milliseconds!!

            hidScanInput();

            u32 kDown = hidKeysDown();
            if (kDown & KEY_START)
                break; // break in order to return to hbmenu

            C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
            C2D_TargetClear(top, clrBackground);
            C2D_SceneBegin(top);

            if (CheckLua(L, luaL_dofile(L, "romfs:/lua/main.lua")))
            {
                lua_getglobal(L, "Update");

                if (lua_isfunction(L, -1))
                {
                    CheckLua(L, lua_pcall(L, 0, 0, 0));
                }
            }

            printf("\x1b[2;1HFPS:     %6.2f\x1b[K", 1000 / deltaTime);
            printf("\x1b[3;1HdeltaT:  %6.2f\x1b[K", deltaTime);

            printf("\x1b[5;1HCPU:     %6.2f%%\x1b[K", C3D_GetProcessingTime() * 6);
            printf("\x1b[6;1HGPU:     %6.2f%%\x1b[K", C3D_GetDrawingTime() * 6);
            printf("\x1b[7;1HCmdBuf:  %6.2f%%\x1b[K", C3D_GetCmdBufUsage() * 100);

            C3D_FrameEnd(0);
        }
    }

    romfsExit();
    gfxExit();
    return 0;
}
#else

int targetFPS = 60;

int main()
{
    lua_State *L = luaL_newstate();

    luaL_openlibs(L);
    lua_register(L, "InitWindow", LuaInit);
    lua_register(L, "SetTargetFPS", LuaSetFPS);

    lua_register(L, "CloseWindow", LuaClose);

    lua_register(L, "DrawRectangle", LuaRectangle);
    lua_register(L, "DrawCircle", LuaCircle);

    SetTraceLogLevel(LOG_ERROR);

    double oldTime;
    double deltaTime;

    if (CheckLua(L, luaL_dofile(L, "../romfs/lua/main.lua")))
    {
        lua_getglobal(L, "Init");

        if (lua_isfunction(L, -1))
        {
            CheckLua(L, lua_pcall(L, 0, 0, 0));
        }
    }

    while (!WindowShouldClose())
    {

        DeltaTime(&oldTime, &deltaTime);

        if (targetFPS > 0) // We want a fixed frame rate
        {
            deltaTime = (1.0 / (double)targetFPS) - deltaTime;
            if (deltaTime > 0.0)
            {
                WaitTime(deltaTime);
                DeltaTime(&oldTime, &deltaTime);
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (CheckLua(L, luaL_dofile(L, "../romfs/lua/main.lua")))
        {
            lua_getglobal(L, "Update");

            if (lua_isfunction(L, -1))
            {
                CheckLua(L, lua_pcall(L, 0, 0, 0));
            }
        }

        DrawText(TextFormat("TARGET FPS: %i", targetFPS), 10, 10, 20, LIME);
        DrawText(TextFormat("CURRENT FPS: %i", (int)(1.0 / deltaTime)), 10, 40, 20, GREEN);
        DrawText(TextFormat("DELTA: %f", deltaTime), 10, 70, 20, DARKGREEN);

        EndDrawing();
    }

    if (CheckLua(L, luaL_dofile(L, "../romfs/lua/main.lua")))
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
#endif