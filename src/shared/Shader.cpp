#include "Shader.hpp"
#include <cstdio> // f�r printf
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

void setUniforms(GLint shaderProgram) {

    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 15.0f, 15.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
    GLint viewLoc = glGetUniformLocation(shaderProgram, "view");
    GLint projLoc = glGetUniformLocation(shaderProgram, "projection");

    if (modelLoc == -1 || viewLoc == -1 || projLoc == -1) {
        std::cerr << "Error: Uniform location not found" << std::endl;
    }

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    GLint objColorLoc = glGetUniformLocation(shaderProgram, "objColor");
    GLint lightColorLoc = glGetUniformLocation(shaderProgram, "lightColor");
    GLint lightPosLoc = glGetUniformLocation(shaderProgram, "lightPos");
    GLint viewPosLoc = glGetUniformLocation(shaderProgram, "viewPos");

    if (objColorLoc == -1 || lightColorLoc == -1 || lightPosLoc == -1 || viewPosLoc == -1) {
        std::cerr << "Error: Uniform location not found" << std::endl;
    }

    glUniform3f(objColorLoc, 1.0f, 0.5f, 0.31f);
    glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);
    glUniform3f(lightPosLoc, 0.0f, 0.0f, 0.0f);
    glUniform3f(viewPosLoc, 0.0f, 0.0f, 5.0f);
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
        projection = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, 0.1f, 1000.0f);
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