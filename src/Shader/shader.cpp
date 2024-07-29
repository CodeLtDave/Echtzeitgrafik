#pragma once

#include <GL/glew.h> // has to be included first!
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>


using namespace Shader;

//Constructor and Destructor;
Shader(const char* source_1, const char* source_2, Shaders shader_1, Shader shader_2); {
    return this;
}
~Shader();

//methods to use and delete shader
void use();
void stop();


//Uniforms
void setUniform(GLint location, int value) {

}

void setUniform(GLint location, float value) {

}

void setUniform(GLint location, vec3 value) {

}

void setUniform(GLint location, vec4 value) {

}

void setUniform(GLint location, mat4 value) {

}


GLint createShaderPipeline(const char* source_1, const char* source_2, Shaders shader_1, Shader shader_2) {
    GLint vertexShader = createShader(source_1, Shader.Vertex);
}


//Helpfull functions
void compileShader(GLint shader) {

}

bool isShaderReady(GLint shader, int status, GLint& success) {

}

GLint createShader(const char* source, int shader) {

}




GLint createShaderPipeline(const char* source_1, const char* source_2)
{
    /* Vertex shader */
    GLint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &source_1, NULL);
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
    glShaderSource(fragmentShader, 1, &source_2, NULL);
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