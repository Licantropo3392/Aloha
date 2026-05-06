#include <Renderer/Shapes/Circle.hpp>

namespace Aloha
{
    Circle::Circle(int x, int y, int radius, Color color)
        : x(x), y(y), radius(radius), color(color) {}

    void Circle::draw()
    {
        Aloha::drawCircle(x, y, radius, color);
    }

    void Circle::setX(int newX)
    {
        x = newX;
    }

    void Circle::setY(int newY)
    {
        y = newY;
    }

    void Circle::setRadius(int newRadius)
    {
        radius = newRadius;
    }

    int Circle::getX()
    {
        return x;
    }

    int Circle::getY()
    {
        return y;
    }

    int Circle::getRadius()
    {
        return radius;
    }
}