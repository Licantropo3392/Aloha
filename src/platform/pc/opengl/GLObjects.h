#pragma once

#include <string>
#include <unordered_map>

#include "ElementBufferObject.h"
#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"
#include "UniformBufferObject.h"
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"

struct Renderer::Impl
{
};

struct VertexBufferObject::Impl
{
    unsigned int rendererId = 0;
};

struct ElementBufferObject::Impl
{
    unsigned int rendererId = 0;
    unsigned int count = 0;
};

struct VertexArrayObject::Impl
{
    unsigned int rendererId = 0;
};

struct UniformBufferObject::Impl
{
    unsigned int rendererId = 0;
};

struct Shader::Impl
{
    unsigned int rendererId = 0;
    std::unordered_map<std::string, int> uniformLocationCache;
};

struct Texture::Impl
{
    unsigned int rendererId = 0;
    std::string filePath;
    int width = 0;
    int height = 0;
    int bpp = 0;
};
