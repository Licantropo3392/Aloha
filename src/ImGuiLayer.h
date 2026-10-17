#pragma once

#include <memory>

class Window;

class ImGuiLayer
{
private:
    struct Impl;
    std::unique_ptr<Impl> m_Impl;

public:
    explicit ImGuiLayer(const Window& window);
    ~ImGuiLayer();

    ImGuiLayer(const ImGuiLayer&) = delete;
    ImGuiLayer& operator=(const ImGuiLayer&) = delete;
    ImGuiLayer(ImGuiLayer&&) = delete;
    ImGuiLayer& operator=(ImGuiLayer&&) = delete;

    void Begin() const;
    void End() const;
    [[nodiscard]] float GetFramerate() const;
};
