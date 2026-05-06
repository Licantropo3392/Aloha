#pragma once

#include <Renderer/platform.hpp>

namespace Aloha
{
    class Rectangle
    {
    private:
        int x, y, width, height;
        Color color;

    public:
        Rectangle(int x, int y, int width, int height, Color color);
        // ~Rectangle();

        void draw();

        void setX(int newX);
        void setY(int newY);
        void setTotalWidth(int newWidth);
        void setHeight(int newHeight);

        int getX();
        int getY();
        int getWidth();
        int getHeight();
    };
}