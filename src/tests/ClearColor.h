#pragma once


#include "../Test.h"

#include "../Window.h"

class Window;

namespace Tests
{
    class ClearColor : public Test
    {
    private:
        float m_ClearColor[4];

    public:
        explicit ClearColor(const Window* window);

        void OnUpdate() override;
        void OnImGuiRender() override;
    };
}
