#include <Renderer/Shapes/Rectangle.hpp>

namespace Aloha
{
    Rectangle::Rectangle(int x, int y, int width, int height, Color color)
        : x(x), y(y), width(width), height(height), color(color) {}
    // Rectangle::~Rectangle() {}

    void Rectangle::draw()
    {
        Aloha::drawRectangle(x, y, width, height, color);
    }

    void Rectangle::setX(int newX)
    {
        x = newX;
    }

    void Rectangle::setY(int newY)
    {
        y = newY;
    }

    void Rectangle::setTotalWidth(int newWidth)
    {
        width = newWidth;
    }

    void Rectangle::setHeight(int newHeight)
    {
        height = newHeight;
    }

    int Rectangle::getX()
    {
        return x;
    }

    int Rectangle::getY()
    {
        return y;
    }

    int Rectangle::getWidth()
    {
        return width;
    }

    int Rectangle::getHeight()
    {
        return height;
    }
}