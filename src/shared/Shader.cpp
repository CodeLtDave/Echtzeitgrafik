#include "Shader.hpp"
#include <cstdio> // für printf
#include <fstream>

#define INFOLOG_LEN 512

std::string readShaderSource(const std::filesystem::path& shaderPath)
{
    std::ifstream shaderFile(shaderPath);
    std::string shaderSource((std::istreambuf_iterator<char>(shaderFile)), std::istreambuf_iterator<char>());
    return shaderSource;
}

GLint createShaderPipeline(const std::filesystem::path& vertexShaderPath, const std::filesystem::path& fragmentShaderPath)
{
    /* Read vertex shader source */
    std::string vertexSource = readShaderSource(vertexShaderPath);
    const char* vertexSourcePtr = vertexSource.c_str();

    /* Read fragment shader source */
    std::string fragmentSource = readShaderSource(fragmentShaderPath);
    const char* fragmentSourcePtr = fragmentSource.c_str();

    /* Vertex shader */
    GLint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSourcePtr, NULL);
    glCompileShader(vertexShader);
    GLint success;
    GLchar infoLog[INFOLOG_LEN];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, INFOLOG_LEN, NULL, infoLog);
        printf("Vertex-Shader compilation failed\n%s\n", infoLog);
    }

    /* Fragment shader */
    GLint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSourcePtr, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, INFOLOG_LEN, NULL, infoLog);
        printf("Fragment-Shader compilation failed\n%s\n", infoLog);
    }

    /* Link shaders */
    GLint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, INFOLOG_LEN, NULL, infoLog);
        printf("Shader linking failed\n%s\n", infoLog);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}
