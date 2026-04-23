#include <platform.hpp>
#include <citro2d.h>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <3ds.h>

namespace Aloha {
    u64 oldTime = osGetTime();
    u64 deltaTime;

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

    C2D_TextBuf textBuffer = C2D_TextBufNew(256);

    C3D_RenderTarget *top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
    C3D_RenderTarget *bottom = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);

    void init(int screenWidth, int screenHeight, const char *title) {
        gfxInitDefault();

        C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
        C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
        C2D_Prepare();
    }

    void setFPS(int fps) {

    }

    void close() {
        C2D_Fini();
        C3D_Fini();
        gfxExit();
    }

    bool shouldClose() {
        hidScanInput();

        u32 kDown = hidKeysDown();
        if (kDown & KEY_START)
            return true; // return true in order to indicate that the application should close
        return false;
    }

    void beginDrawing(Color color) {
        // C3D_FrameBegin(C3D_FRAME_NONBLOCK);
        C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
        C2D_TargetClear(top, C2D_Color32(color.r, color.g, color.b, color.a));
        C2D_SceneBegin(top);

        C2D_TargetClear(bottom, C2D_Color32(color.r, color.g, color.b, color.a));
    }

    void endDrawing() {
        deltaTime = (osGetTime() - oldTime);
        oldTime = osGetTime();
        C2D_SceneBegin(bottom);

        C2D_TextBufClear(textBuffer);

        FPSstring = "FPS: " + std::to_string(1 / ((float)deltaTime / 1000));
        deltaTimeString = "DELTA: " + std::to_string((float)deltaTime / 1000);
        CPUstring = "CPU: " + std::to_string((C3D_GetProcessingTime() * 6));
        GPUstring = "GPU: " + std::to_string((C3D_GetDrawingTime() * 6));
        CmdBufstring = "CmdBuf: " + std::to_string((C3D_GetCmdBufUsage() * 100));

        C2D_TextParse(&FPS, textBuffer, FPSstring.c_str());
        C2D_TextOptimize(&FPS);

        C2D_TextParse(&deltaTimeText, textBuffer, deltaTimeString.c_str());
        C2D_TextOptimize(&deltaTimeText);

        C2D_TextParse(&CPUText, textBuffer, CPUstring.c_str());
        C2D_TextOptimize(&CPUText);

        C2D_TextParse(&GPUText, textBuffer, GPUstring.c_str());
        C2D_TextOptimize(&GPUText);

        C2D_TextParse(&CmdBufText, textBuffer, CmdBufstring.c_str());
        C2D_TextOptimize(&CmdBufText);

        C2D_DrawText(&FPS, C2D_WithColor, 10, 10, 0, 1, 1, C2D_Color32(255, 255, 255, 255));
        C2D_DrawText(&deltaTimeText, C2D_WithColor, 10, 30, 0, 1, 1, C2D_Color32(255, 255, 255, 255));
        C2D_DrawText(&CPUText, C2D_WithColor, 10, 50, 0, 1, 1, C2D_Color32(255, 255, 255, 255));
        C2D_DrawText(&GPUText, C2D_WithColor, 10, 70, 0, 1, 1, C2D_Color32(255, 255, 255, 255));
        C2D_DrawText(&CmdBufText, C2D_WithColor, 10, 90, 0, 1, 1, C2D_Color32(255, 255, 255, 255));

        C3D_FrameEnd(0);
    }

    void drawText(const char* text, int posX, int posY, int fontSize, Color color) {
        C2D_Text citroText;

        C2D_TextParse(&citroText, textBuffer, text);
        C2D_TextOptimize(&citroText);
        C2D_DrawText(&citroText, C2D_WithColor, posX, posY, 0, fontSize / 10, fontSize / 10, C2D_Color32(color.r, color.g, color.b, color.a));
    }

    void drawRectangle(int x, int y, int width, int height, Color color) {
        u32 color3DS = C2D_Color32(color.r, color.g, color.b, color.a);
        C2D_DrawRectangle(x, y, 0, width, height, color3DS, color3DS, color3DS, color3DS);
    }

    void drawCircle(int centerX, int centerY, int radius, Color color) {
        u32 color3DS = C2D_Color32(color.r, color.g, color.b, color.a);
        C2D_DrawCircle(centerX, centerY, 0, radius, color3DS, color3DS, color3DS, color3DS);
    }
}
