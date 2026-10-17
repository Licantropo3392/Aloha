#include "Texture.h"

#include <utility>

#include <stb_image/stb_image.h>

#include "glDebug.h"
#include "GLObjects.h"
#ifdef TRACY_ENABLE
#include <tracy/Tracy.hpp>
#endif

Texture::Texture(std::string m_file_path)
    : m_Impl(std::make_unique<Impl>())
{
#ifdef TRACY_ENABLE
    ZoneScopedN("Texture::Load and upload");
#endif
    stbi_set_flip_vertically_on_load(1);
    m_Impl->filePath = std::move(m_file_path);
    unsigned char* data = stbi_load(m_Impl->filePath.c_str(), &m_Impl->width, &m_Impl->height, &m_Impl->bpp, 4);

    glGenTextures(1, &m_Impl->rendererId);
    glBindTexture(GL_TEXTURE_2D, m_Impl->rendererId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Impl->width, m_Impl->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture: " << m_Impl->filePath
               << " reason: " << stbi_failure_reason() << std::endl;
    }

    stbi_image_free(data);
}

Texture::~Texture()
{
    if (m_Impl)
        glDeleteTextures(1, &m_Impl->rendererId);
}

Texture::Texture(Texture&&) noexcept = default;

void Texture::Bind(const unsigned int slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_Impl->rendererId);
}

void Texture::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

int Texture::GetWidth() const
{
    return m_Impl->width;
}

int Texture::GetHeight() const
{
    return m_Impl->height;
}

int Texture::GetBPP() const
{
    return m_Impl->bpp;
}
