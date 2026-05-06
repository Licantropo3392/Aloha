#include <Renderer/Shapes/Text.hpp>

namespace Aloha
{
    Text::Text(const char *text, int x, int y, int fontSize, Color color)
        : text(text), x(x), y(y), fontSize(fontSize), color(color) {}

    void Text::draw()
    {
        Aloha::drawText(text, x, y, fontSize, color);
    }

    void Text::setText(const char *newText)
    {
        text = newText;
    }

    void Text::setX(int newX)
    {
        x = newX;
    }

    void Text::setY(int newY)
    {
        y = newY;
    }

    void Text::setFontSize(int newFontSize)
    {
        fontSize = newFontSize;
    }

    const char *Text::getText()
    {
        return text;
    }

    int Text::getX()
    {
        return x;
    }

    int Text::getY()
    {
        return y;
    }

    int Text::getFontSize()
    {
        return fontSize;
    }
}