#pragma once

#include <memory>
#include <string>


class Texture
{
private:
    struct Impl;
    std::unique_ptr<Impl> m_Impl;

public:
    explicit Texture(std::string  m_file_path);
    ~Texture();

    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;
    Texture(Texture&&) noexcept;
    Texture& operator=(Texture&&) = delete;

    void Bind(unsigned int slot = 0) const;
    static void Unbind() ;

    [[nodiscard]] int GetWidth() const;
    [[nodiscard]] int GetHeight() const;
    [[nodiscard]] int GetBPP() const;
};
