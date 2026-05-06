#pragma once

#include <Renderer/platform.hpp>

namespace Aloha
{
    class Circle
    {
    private:
        int x, y, radius;
        Color color;

    public:
        Circle(int x, int y, int radius, Color color);
        // ~Circle();

        void draw();

        void setX(int newX);
        void setY(int newY);
        void setRadius(int newRadius);

        int getX();
        int getY();
        int getRadius();
    };
}