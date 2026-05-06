#include <Window/Window.hpp>

namespace Aloha
{
    Window::Window(int width, int height, int fps, const char *title, int screenTarget, bool doubleScreen)
    {
        this->setDoubleScreen(doubleScreen);
        this->setTargetScreen(screenTarget);

        this->setWidth(width);
        this->setHeight(height);
        this->setFps(fps);
        this->setTitle(title);

        this->init();
    }

    Window::Window(int width, int height, int fps, const char *title, int screenTarget)
    {
        Window(width, height, fps, title, screenTarget, false);
    }

    void Window::init()
    {
        Aloha::WindowImpl::create(this->width, this->height, this->title);
    }

    void Window::close()
    {
        Aloha::WindowImpl::close();
    }

    bool Window::shouldClose()
    {
        return Aloha::WindowImpl::shouldClose();
    }

    void Window::beginDrawing(Color color)
    {
        Aloha::WindowImpl::beginDrawing(color);
    }

    void Window::endDrawing()
    {
        Aloha::WindowImpl::endDrawing();
    }

    void Window::setDoubleScreen(bool doubleScreen)
    {
        this->doubleScreen = doubleScreen;
    }

    void Window::setTargetScreen(int screen)
    {
        this->screenTarget = screen;
    }

    int Window::getTargetScreen()
    {
        return this->screenTarget;
    }

    bool Window::isDoubleScreen()
    {
        return this->doubleScreen;
    }

    void Window::setWidth(int width)
    {
#if defined(__3DS__)
        width = 400;
#endif

        this->width = width;
    }

    void Window::setHeight(int height)
    {
#if defined(__3DS__)
        height = 240;
#endif

        this->height = height;
    }

    void Window::setFps(int fps)
    {
        this->fps = fps;
        Aloha::WindowImpl::setFPS(this->fps);
    }

    void Window::setTitle(const char *title)
    {
        this->title = title;
    }

    int Window::getWidth()
    {
        return this->width;
    }

    int Window::getHeight()
    {
        return this->height;
    }

    int Window::getFps()
    {
        return this->fps;
    }

    const char *Window::getTitle()
    {
        return this->title;
    }
}
