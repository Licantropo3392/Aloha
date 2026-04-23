#pragma once
#include <platform.hpp>

namespace Aloha {
    class Rectangle {
        private:
            int x, y, width, height;
            Color color;
        public:
            Rectangle(int x, int y, int width, int height, Color color)
                : x(x), y(y), width(width), height(height), color(color) {}
            // ~Rectangle();

            inline void setX(int newX) { x = newX; }
            inline void setY(int newY) { y = newY; }
            inline void setWidth(int newWidth) { width = newWidth; }
            inline void setHeight(int newHeight) { height = newHeight; }

            inline int getX() { return x; }
            inline int getY() { return y; }
            inline int getWidth() { return width; }
            inline int getHeight() { return height; }

            inline void draw() { Aloha::drawRectangle(x, y, width, height, color); }
    };

    class Circle {
        private:
            int x, y, radius;
            Color color;
        public:
            Circle(int x, int y, int radius, Color color)
                : x(x), y(y), radius(radius), color(color) {};
            // ~Circle();
    
            inline void setX(int newX) { x = newX; }
            inline void setY(int newY) { y = newY; }
            inline void setRadius(int newRadius) { radius = newRadius; }

            inline int getX() { return x; }
            inline int getY() { return y; }
            inline int getRadius() { return radius; }

            inline void draw() { Aloha::drawCircle(x, y, radius, color); }
    };

    class Text {
        private:
            const char* text;
            int x, y, fontSize;
            Color color;
        public:
            Text(const char* text, int x, int y, int fontSize, Color color)
                : text(text), x(x), y(y), fontSize(fontSize), color(color) {};
            // ~Text();

            inline void setText(const char* newText) { text = newText; }
            inline void setX(int newX) { x = newX; }
            inline void setY(int newY) { y = newY; }
            inline void setFontSize(int newFontSize) { fontSize = newFontSize; }

            inline const char* getText() { return text; }
            inline int getX() { return x; }
            inline int getY() { return y; }
            inline int getFontSize() { return fontSize; }

            inline void draw() { Aloha::drawText(text, x, y, fontSize, color); }
    };
}