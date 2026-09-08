#include "Shader.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "glad/glad.h"
#include "glDebug.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const std::string& filePath)
{
    auto [VertexSource, FragmentSource] = ParseShader(filePath);
    m_RendererID = CreateShader(VertexSource, FragmentSource);
}

Shader::~Shader()
{
    glDeleteProgram(m_RendererID);
}

void Shader::Bind() const
{
    glUseProgram(m_RendererID);
}

void Shader::Unbind()
{
    glUseProgram(0);
}

void Shader::SetUniform(const std::string& name, const glm::vec3& vec)
{
    glUniform3f(GetUniformLocation(name),  glm::value_ptr(vec)[0], glm::value_ptr(vec)[1], glm::value_ptr(vec)[2]);
}

void Shader::SetUniform(const std::string& name, const int v0)
{
    glUniform1i(GetUniformLocation(name), v0);
}

void Shader::SetUniform(const std::string& name, const float v0, const float v1)
{
    glUniform2f(GetUniformLocation(name), v0, v1);
}

void Shader::SetUniform(const std::string& name, const float v0, const float v1, const float v2)
{
    glUniform3f(GetUniformLocation(name), v0, v1, v2);
}

void Shader::SetUniform(const std::string& name, const float v0, const float v1, const float v2, const float v3)
{
    glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

ShaderProgramSource Shader::ParseShader(const std::string& filePath)
{
    std::ifstream stream(filePath);

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream result[2];
    auto type = ShaderType::NONE;

    while (getline(stream, line))
    {
        if (line.find("#vertex") != std::string::npos)
            type = ShaderType::VERTEX;
        else if (line.find("#fragment") != std::string::npos)
            type = ShaderType::FRAGMENT;
        else
            result[static_cast<int>(type)] << line << "\n";
    }

    return { .VertexSource = result[0].str(), .FragmentSource = result[1].str() };
}

unsigned int Shader::CompileShader(const unsigned int type, const std::string& source)
{
    const unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        /*int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);*/
        char infoLog[512];
        glGetShaderInfoLog(id, sizeof(infoLog), nullptr, infoLog);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader\n";
        std::cout << infoLog << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    const unsigned int program = glCreateProgram();
    const unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    const unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

unsigned int Shader::GetUniformLocation(const std::string& name)
{
    if (m_UniformLocationCache.contains(name))
        return m_UniformLocationCache[name];

    const int location = glGetUniformLocation(m_RendererID, name.c_str());
    if (location == -1)
        std::cout << "Uniform " << name << " not found\n";

    m_UniformLocationCache[name] = location;
    return location;
}
