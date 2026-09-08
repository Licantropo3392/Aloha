#ifndef LEARN_OPENGL_SHADER_H
#define LEARN_OPENGL_SHADER_H


#include <string>
#include <unordered_map>

#include <glm/glm.hpp>

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

class Shader
{
private:
    unsigned int m_RendererID;
    std::unordered_map<std::string, int> m_UniformLocationCache;
public:
    explicit Shader(const std::string& filePath);
    ~Shader();

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


#endif //LEARN_OPENGL_SHADER_H
