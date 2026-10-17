#pragma once


#include <memory>
#include <string>

#include <glm/glm.hpp>

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};
class Shader
{
private:
    struct Impl;
    std::unique_ptr<Impl> m_Impl;
public:
    explicit Shader(const std::string& filePath);
    ~Shader();

    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;
    Shader(Shader&&) noexcept;
    Shader& operator=(Shader&&) = delete;

    void Bind() const;
    static void Unbind();

    void SetUniform(const std::string& name, const glm::vec3& vec);

    void SetUniform(const std::string& name, int v0);
    void SetUniform(const std::string& name, float v0, float v1);
    void SetUniform(const std::string& name, float v0, float v1, float v2);
    void SetUniform(const std::string& name, float v0, float v1, float v2, float v3);

private:
    static ShaderProgramSource ParseShader(const std::string& filePath);
    static unsigned int CompileShader(unsigned int type, const std::string& source);
    static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
    [[nodiscard]] unsigned int GetUniformLocation(const std::string& name);
};
