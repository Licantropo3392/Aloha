#ifndef LEARN_OPENGL_TEXTURE_H
#define LEARN_OPENGL_TEXTURE_H
#include <string>


class Texture
{
private:
    unsigned int m_RendererID;
    std::string m_FilePath;
    unsigned char* m_Data;
    int m_Width, m_Height, m_BPP;

public:
    explicit Texture(std::string  m_file_path);
    ~Texture();

    void Bind(unsigned int slot = 0) const;
    static void Unbind() ;

    [[nodiscard]] int GetWidth() const
    {
        return m_Width;
    }

    [[nodiscard]] int GetHeight() const
    {
        return m_Height;
    }

    [[nodiscard]] int GetBPP() const
    {
        return m_BPP;
    }
};


#endif