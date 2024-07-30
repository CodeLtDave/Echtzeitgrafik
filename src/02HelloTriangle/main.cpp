#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h> // has to be included first!
#include <GLFW/glfw3.h>
#include <assimp/Importer.hpp>
#include <glm/glm.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "shared/functions.h"
#include "shared/Shader.hpp"
#include "shared/data.h"
#include "shared/GeometryBuffer.hpp"

void spaceBarPressed(GLFWwindow* window, int key, int scancode, int action, int mods);

int main(int argc, char** argv) 
{
    std::cout << "Hello HelloTriangle!" << std::endl;

    GLFWwindow* window = initAndCreateWindow();
    glViewport(0, 0, 800, 600);

    GLint shaderProgram = createShaderPipeline(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);
    
    GeometryBuffer geometryBuffer;
    //TODO Cube in seperate Main
    geometryBuffer.bindAndUploadBufferData(sizeof(cube), cube, GL_STATIC_DRAW);

    /* Position attribute */
    geometryBuffer.bindVertexArray();
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    /* Color attribute */
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    geometryBuffer.unbindVertexArray();

    glUseProgram(shaderProgram);
    glPolygonMode(GL_FRONT_AND_BACK, GL_TRIANGLES);

    /* Register Space Bar to Projection Swap*/
    glfwSetWindowUserPointer(window, &shaderProgram);
    glfwSetKeyCallback(window, spaceBarPressed);

    setShaderUniforms(shaderProgram);

    while (glfwWindowShouldClose(window) == 0)
    {
        setContinousUniforms(shaderProgram);

        // clear the window
        glClearColor(0.0f, 0.1f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        geometryBuffer.bindVertexArray();
        glDrawArrays(GL_TRIANGLES, 0, 36);
        geometryBuffer.unbindVertexArray();

        // swap buffer
        glfwSwapBuffers(window);

        // process user events
        glfwPollEvents();

        calculateFPS();
    }

    glfwTerminate();
}

void spaceBarPressed(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        std::cout << "Space Bar Pressed" << std::endl;
        GLint* shaderProgram = static_cast<GLint*>(glfwGetWindowUserPointer(window));
        swapPerspective(*shaderProgram);
    }
}