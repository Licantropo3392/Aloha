#pragma once

#include <Renderer/platform.hpp>

namespace Aloha
{
    class Text
    {
    private:
        const char *text;
        int x, y, fontSize;
        Color color;

    public:
        Text(const char *text, int x, int y, int fontSize, Color color);
        // ~Text();

        void draw();

        void setText(const char *newText);
        void setFontSize(int newFontSize);
        void setX(int newX);
        void setY(int newY);

        const char *getText();
        int getFontSize();
        int getX();
        int getY();
    };
}