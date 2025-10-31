#include "LuaUtilities.hpp"
#include "LuaDraw.hpp"

#ifdef __3DS__
#include <citro2d.h>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <3ds.h>
#else
#include <raylib.h>
#endif
#include <iostream>

int targetFPS;

int main() {
    #ifdef __3DS__
    gfxInitDefault();

    // consoleInit(GFX_BOTTOM, NULL);

    const u32 clrBackground = C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF);

    u64 oldTime = osGetTime();

    std::string FPSstring;
    std::string deltaTimeString;
    std::string CPUstring;
    std::string GPUstring;
    std::string CmdBufstring;

    C2D_Text FPS;
    C2D_Text deltaTimeText;
    C2D_Text CPUText;
    C2D_Text GPUText;
    C2D_Text CmdBufText;

    C2D_TextBuf bufFPS = C2D_TextBufNew(256);
    C2D_TextBuf bufDeltaTime = C2D_TextBufNew(256);
    C2D_TextBuf bufCPU = C2D_TextBufNew(256);
    C2D_TextBuf bufGPU = C2D_TextBufNew(256);
    C2D_TextBuf bufCmdBuf = C2D_TextBufNew(256);

    Result rc = romfsInit();
    if (rc) {
        printf("romfsInit: %08lX\n", rc);
        return 1;
    }
    #else
    SetTraceLogLevel(LOG_ERROR);
    double oldTime = GetTime();
    #endif

    double deltaTime;

    lua_State *L = luaL_newstate();

    luaL_openlibs(L);
    lua_register(L, "InitWindow", LuaInit);
    lua_register(L, "SetTargetFPS", LuaSetFPS);

    lua_register(L, "CloseWindow", LuaClose);

    lua_register(L, "DrawRectangle", LuaRectangle);
    lua_register(L, "DrawCircle", LuaCircle);

    
    // Load core utils and rendering modules first so their globals exist
    CheckLua(L, luaL_dofile(L, 
        #ifdef __3DS__
        "romfs:/lua/Aloha/Utils.lua"
        #else
        "../romfs/lua/Aloha/Utils.lua"
        #endif
    ));

    CheckLua(L, luaL_dofile(L, 
        #ifdef __3DS__
        "romfs:/lua/Aloha/rendering/Color.lua"
        #else
        "../romfs/lua/Aloha/rendering/Color.lua"
        #endif
    ));
    CheckLua(L, luaL_dofile(L, 
        #ifdef __3DS__
        "romfs:/lua/Aloha/rendering/Window.lua"
        #else
        "../romfs/lua/Aloha/rendering/Window.lua"
        #endif
    ));
    CheckLua(L, luaL_dofile(L, 
        #ifdef __3DS__
        "romfs:/lua/Aloha/rendering/Rectangle.lua"
        #else
        "../romfs/lua/Aloha/rendering/Rectangle.lua"
        #endif
    ));
    CheckLua(L, luaL_dofile(L, 
        #ifdef __3DS__
        "romfs:/lua/Aloha/rendering/Circle.lua"
        #else
        "../romfs/lua/Aloha/rendering/Circle.lua"
        #endif
    ));

    // Finally load Aloha which wires module globals into the Aloha table
    CheckLua(L, luaL_dofile(L, 
        #ifdef __3DS__
        "romfs:/lua/Aloha/Aloha.lua"
        #else
        "../romfs/lua/Aloha/Aloha.lua"
        #endif
    ));

    if (CheckLua(L, luaL_dofile(L, 
        #ifdef __3DS__
        "romfs:/lua/main.lua"
        #else
        "../romfs/lua/main.lua"
        #endif
    )))
    {
        #ifdef __3DS__
        lua_getglobal(L, "Aloha");
        if (lua_istable(L, -1)) {
            lua_getfield(L, -1, "__3DS__");
            if (lua_isboolean(L, -1)) {
                lua_pushboolean(L, true);
                lua_setfield(L, -3, "__3DS__");
            }
        }
        #endif

        lua_getglobal(L, "Init");
        if (lua_isfunction(L, -1)) {
            CheckLua(L, lua_pcall(L, 0, 0, 0));
        }
    }

    #ifdef __3DS__
    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
    C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
    C2D_Prepare();

    C3D_RenderTarget *top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
    C3D_RenderTarget *bottom = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);

    while (aptMainLoop()) {
        // gspWaitForVBlank();

        hidScanInput();

        u32 kDown = hidKeysDown();
        if (kDown & KEY_START)
            break; // break in order to return to hbmenu

        C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
        C2D_TargetClear(top, clrBackground);
        C2D_SceneBegin(top);
    #else
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
    #endif
        DeltaTime(&oldTime, &deltaTime);
        
        lua_getglobal(L, "window");
        if (lua_istable(L, -1)) {
            lua_pushnumber(L, deltaTime);
            lua_setfield(L, -2, "deltaTime");
        }

        lua_getglobal(L, "Update");
        if (lua_isfunction(L, -1)) {
            CheckLua(L, lua_pcall(L, 0, 0, 0));
        }
        #ifdef __3DS__
        C2D_TargetClear(bottom, clrBackground);
        C2D_SceneBegin(bottom);

        C2D_TextBufClear(bufFPS);
        C2D_TextBufClear(bufDeltaTime);
        C2D_TextBufClear(bufCPU);
        C2D_TextBufClear(bufGPU);
        C2D_TextBufClear(bufCmdBuf);

        FPSstring = "FPS: " + std::to_string((int)(1 / deltaTime));
        deltaTimeString = "DELTA: " + std::to_string(deltaTime);
        CPUstring = "CPU: " + std::to_string((C3D_GetProcessingTime() * 6));
        GPUstring = "GPU: " + std::to_string((C3D_GetDrawingTime() * 6));
        CmdBufstring = "CmdBuf: " + std::to_string((C3D_GetCmdBufUsage() * 100));

        C2D_TextParse(&FPS, bufFPS, FPSstring.c_str());
        C2D_TextOptimize(&FPS);

        C2D_TextParse(&deltaTimeText, bufDeltaTime, deltaTimeString.c_str());
        C2D_TextOptimize(&deltaTimeText);

        C2D_TextParse(&CPUText, bufCPU, CPUstring.c_str());
        C2D_TextOptimize(&CPUText);

        C2D_TextParse(&GPUText, bufGPU, GPUstring.c_str());
        C2D_TextOptimize(&GPUText);

        C2D_TextParse(&CmdBufText, bufCmdBuf, CmdBufstring.c_str());
        C2D_TextOptimize(&CmdBufText);

        C2D_DrawText(&FPS, C2D_AlignLeft, 10, 10, 0, 1, 1);
        C2D_DrawText(&deltaTimeText, C2D_AlignLeft, 10, 30, 0, 1, 1);
        C2D_DrawText(&CPUText, C2D_AlignLeft, 10, 50, 0, 1, 1);
        C2D_DrawText(&GPUText, C2D_AlignLeft, 10, 70, 0, 1, 1);
        C2D_DrawText(&CmdBufText, C2D_AlignLeft, 10, 90, 0, 1, 1);

        // printf("\x1b[2;1HFPS:     %6.2f\x1b[K", 1000 / deltaTime);
        // printf("\x1b[3;1HdeltaT:  %6.2f\x1b[K", deltaTime);

        // printf("\x1b[5;1HCPU:     %6.2f%%\x1b[K", C3D_GetProcessingTime() * 6);
        // printf("\x1b[6;1HGPU:     %6.2f%%\x1b[K", C3D_GetDrawingTime() * 6);
        // printf("\x1b[7;1HCmdBuf:  %6.2f%%\x1b[K", C3D_GetCmdBufUsage() * 100);

        C3D_FrameEnd(0);
    }
        #else
        DrawText(TextFormat("TARGET FPS: %i", targetFPS), 10, 10, 20, LIME);
        DrawText(TextFormat("RAW FPS: %i", (int)(1.0 / deltaTime)), 10, 40, 20, GREEN);
        DrawText(TextFormat("DELTA: %f", deltaTime), 10, 70, 20, DARKGREEN);

        EndDrawing();
    }
        #endif

    lua_getglobal(L, "Unload");

    if (lua_isfunction(L, -1)) {
        CheckLua(L, lua_pcall(L, 0, 0, 0));
    }

    lua_close(L);

    return 0;
}