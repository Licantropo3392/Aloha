#vertex
#version 450 core

layout (location = 0) in vec3 aPos;

layout (binding = 0) uniform Matrices
{
    mat4 model;
    mat4 view;
    mat4 projection;
};

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}

#fragment
#version 450 core

out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0);
}