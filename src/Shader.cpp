// Shader.cpp
#include "Shader.hpp"
#include <iostream>

Shader::Shader(const GLchar* vertexSource, const GLchar* fragmentSource) {
    GLuint vertexShader = compileShader(vertexSource, GL_VERTEX_SHADER);
    GLuint fragmentShader = compileShader(fragmentSource, GL_FRAGMENT_SHADER);

    linkProgram(vertexShader, fragmentShader);
}

Shader::~Shader() {
    glDeleteProgram(programID);
}

void Shader::use() const {
    glUseProgram(programID);
}

void Shader::setUniform(GLint location, int value) const {
    glUniform1i(location, value);
}

void Shader::setUniform(GLint location, float value) const {
    glUniform1f(location, value);
}

void Shader::setUniform(GLint location, const glm::vec3& value) const {
    glUniform3fv(location, 1, glm::value_ptr(value));
}

void Shader::setUniform(GLint location, const glm::vec4& value) const {
    glUniform4fv(location, 1, glm::value_ptr(value));
}

void Shader::setUniform(GLint location, const glm::mat4& value) const {
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

GLuint Shader::compileShader(const GLchar* source, GLenum shaderType) const {
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return shader;
}

void Shader::linkProgram(GLuint vertexShader, GLuint fragmentShader) {
    programID = glCreateProgram();
    glAttachShader(programID, vertexShader);
    glAttachShader(programID, fragmentShader);
    glLinkProgram(programID);

    GLint success;
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(programID, 512, nullptr, infoLog);
        std::cerr << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}
