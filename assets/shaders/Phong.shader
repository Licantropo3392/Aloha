#vertex
#version 450 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

layout (binding = 0) uniform Matrices
{
    mat4 model;
    mat4 view;
    mat4 projection;
};

out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    TexCoord = aTexCoord;

    Normal = mat3(model) * aNormal;
    FragPos = vec3(model * vec4(aPos, 1.0));
}

#fragment
#version 450 core

out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

layout (location = 0) uniform sampler2D texture1;
layout (location = 1) uniform sampler2D texture2;
layout (location = 2) uniform vec3 lightPos;
layout (location = 3) uniform vec3 viewPos;

void main()
{
    vec3 lightColor = vec3(1.0, 1.0, 1.0);
    vec4 objectColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);

    // Ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Specular
    float specularStrength = 0.5;

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 lighting = ambient + diffuse + specular;
    FragColor = vec4(lighting * objectColor.rgb, objectColor.a);
}