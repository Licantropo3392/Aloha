#pragma once

#include <Window/platform.hpp>

namespace Aloha
{
    class Window
    {
    private:
        unsigned int width, height, fps, screenTarget;
        const char *title;
        bool doubleScreen;

    public:
        Window(int width, int height, int fps, const char *title, int screenTarget);
        Window(int width, int height, int fps, const char *title, int screenTarget, bool doubleScreen);

        void init();
        void close();
        bool shouldClose();

        void beginDrawing(Color color);
        void endDrawing();

        void setDoubleScreen(bool doubleScreen);
        void setTargetScreen(int screen);

        int getTargetScreen();
        bool isDoubleScreen();

        void setWidth(int width);
        void setHeight(int height);
        void setFps(int fps);
        void setTitle(const char *title);

        int getWidth();
        int getHeight();
        int getFps();
        const char *getTitle();
    };
}
