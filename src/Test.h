#ifndef LEARN_OPENGL_TEST_H
#define LEARN_OPENGL_TEST_H


#include <functional>
#include <string>
#include <vector>

#include "Window.h"

namespace Tests
{
    class Test
    {
    protected:
        const Window* m_Window;

    public:
        explicit Test(const Window* window);
        virtual ~Test() = default;

        virtual void OnUpdate() {}
        virtual void OnImGuiRender() {}
    };

    class TestMenu : public Test
    {
    private:
        Test*& m_CurrentTest;
        std::vector<std::pair<std::string, std::function<Test*()>>> m_Tests;

    public:
        explicit TestMenu(const Window* window, Test*& currentTest);

        void OnUpdate() override;
        void OnImGuiRender() override;

        template <typename T>
        void Register(const std::string& name)
        {
            m_Tests.push_back(std::make_pair(name, [this]() { return new T(m_Window); }));
        }
    };
}

#endif
