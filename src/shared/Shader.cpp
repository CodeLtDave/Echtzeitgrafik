#include "Shader.hpp"
#include <cstdio> // für printf
#include <fstream>
#include <glm/ext/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

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

void setShaderUniforms(GLint shaderProgram)
{
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection;
    
    //model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 1000.0f);

    int viewLoc = glGetUniformLocation(shaderProgram, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    int perspectiveLoc = glGetUniformLocation(shaderProgram, "projection");
    glUniformMatrix4fv(perspectiveLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

void setContinousUniforms(GLint shaderProgram)
{
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

    int modelLoc = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
}

void swapPerspective(GLint shaderProgram) {
    glm::mat4 projection;
    if (projectionIsPerspective) {
		projectionIsPerspective = false;
        projection = glm::ortho(-40.0f, 40.0f, -30.0f, 30.0f, 0.1f, 1000.0f);
        std::cout << "Projection changed to orthogonal" << std::endl;
    }
    else {
        projectionIsPerspective = true;
        projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 1000.0f);
        std::cout << "Projection changed to perspective" << std::endl;
    }

    int perspectiveLoc = glGetUniformLocation(shaderProgram, "projection");
    glUniformMatrix4fv(perspectiveLoc, 1, GL_FALSE, glm::value_ptr(projection));
}