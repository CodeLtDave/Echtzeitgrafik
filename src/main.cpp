// main.cpp
#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <assimp/Importer.hpp>
#include <glm/glm.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "shared/functions.h"
#include "Shader.hpp"

// Vertex-Daten für ein einfaches Dreieck
GLfloat vertices[] = {
    // Position         // Farbe
    0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // Oben
   -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // Links
    0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // Rechts
};

// Shader-Quellen
static const GLchar* simpleVertexShaderSource =
"#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"layout (location = 1) in vec3 color;\n"
"out vec3 ourColor;\n"
"void main() {\n"
" gl_Position = vec4(position, 1.0f);\n"
" ourColor = color;\n"
"}\0";

static const GLchar* simpleFragmentShaderSource =
"#version 330 core\n"
"in vec3 ourColor;\n"
"out vec4 color;\n"
"void main() {\n"
" color = vec4(ourColor, 1.0f);\n"
"}\0";

int main(int argc, char** argv) 
{
    std::cout << "Hello World!" << std::endl;

    GLFWwindow* window = initAndCreateWindow();
    glViewport(0, 0, 800, 600);

    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    Shader shader(simpleVertexShaderSource, simpleFragmentShaderSource);

    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    while (glfwWindowShouldClose(window) == 0)
    {
        glClearColor(0.0f, 0.1f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();

    return 0;
}
