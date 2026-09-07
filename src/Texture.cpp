#include "Texture.h"

#include <utility>

#include <stb_image/stb_image.h>

#include "glDebug.h"

Texture::Texture(std::string m_file_path)
    : m_RendererID(0), m_FilePath(std::move(m_file_path)), m_Data(nullptr), m_Width(0), m_Height(0), m_BPP(0)
{
    stbi_set_flip_vertically_on_load(1);
    m_Data = stbi_load(m_FilePath.c_str(), &m_Width, &m_Height, &m_BPP, 4);

    glGenTextures(1, &m_RendererID);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    if (m_Data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_Data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture: " << m_FilePath
               << " reason: " << stbi_failure_reason() << std::endl;
    }

    stbi_image_free(m_Data);
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_RendererID);
    // stbi_image_free(m_Data);
}

void Texture::Bind(const unsigned int slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);
}

void Texture::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
