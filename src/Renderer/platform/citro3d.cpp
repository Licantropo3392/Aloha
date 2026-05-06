#include <Renderer/platform.hpp>

#include <citro2d.h>

namespace Aloha
{
    C2D_Text text;

    C2D_TextBuf textBuffer = C2D_TextBufNew(512);

    void drawText(const char *text, int posX, int posY, int fontSize, Color color)
    {
        C2D_Text citroText;

        C2D_TextParse(&citroText, textBuffer, text);
        C2D_TextOptimize(&citroText);
        C2D_DrawText(&citroText, C2D_WithColor, posX, posY, 0, fontSize / 10, fontSize / 10, C2D_Color32(color.r, color.g, color.b, color.a));
        C2D_TextBufClear(textBuffer);
    }

    void drawRectangle(int x, int y, int width, int height, Color color)
    {
        u32 color3DS = C2D_Color32(color.r, color.g, color.b, color.a);
        C2D_DrawRectangle(x, y, 0, width, height, color3DS, color3DS, color3DS, color3DS);
    }

    void drawCircle(int centerX, int centerY, int radius, Color color)
    {
        u32 color3DS = C2D_Color32(color.r, color.g, color.b, color.a);
        C2D_DrawCircle(centerX, centerY, 0, radius, color3DS, color3DS, color3DS, color3DS);
    }
}