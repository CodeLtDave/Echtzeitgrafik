#include "Shader.hpp"
#include <cstdio> // f�r printf
#include <fstream>
#include <glm/ext/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "data.h"

#define INFOLOG_LEN 512

Shader::Shader()
    : m_shaderProgram(0)
{}

Shader::Shader(const std::filesystem::path& vertexShaderPath, const std::filesystem::path& fragmentShaderPath)
{
    createShaderProgram(vertexShaderPath, fragmentShaderPath);
    glUseProgram(m_shaderProgram);
}

void Shader::createShaderProgram(const std::filesystem::path& vertexShaderPath, const std::filesystem::path& fragmentShaderPath) {
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
    m_shaderProgram = glCreateProgram();
    glAttachShader(m_shaderProgram, vertexShader);
    glAttachShader(m_shaderProgram, fragmentShader);
    glLinkProgram(m_shaderProgram);
    glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(m_shaderProgram, INFOLOG_LEN, NULL, infoLog);
        printf("Shader linking failed\n%s\n", infoLog);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

std::string Shader::readShaderSource(const std::filesystem::path& shaderPath)
{
    std::ifstream shaderFile(shaderPath);
    std::string shaderSource((std::istreambuf_iterator<char>(shaderFile)), std::istreambuf_iterator<char>());
    return shaderSource;
}

GLint Shader::getLocation(const char* uniformName) {
    GLint location = glGetUniformLocation(m_shaderProgram, uniformName);
    if (location == -1) {
		std::cerr << "Error: " << uniformName << "not found" << std::endl;
	}
    return location;
}

void Shader::setUniform(GLint location, glm::mat4 matrix) {
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::setUniform(GLint location, glm::vec3 value) {
	glUniform3f(location, value.x, value.y, value.z);
}

