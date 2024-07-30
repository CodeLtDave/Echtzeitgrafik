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
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>

int main(int argc, char** argv) 
{
    std::cout << "Hello HelloTriangle!" << std::endl;

    GLFWwindow* window = initAndCreateWindow();
    glViewport(0, 0, 800, 600);

    GLint shaderProgram = createShaderPipeline(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);
    
    GeometryBuffer geometryBuffer;
    geometryBuffer.bindAndUploadBufferData(sizeof(triangle), triangle, GL_STATIC_DRAW);

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

    while (glfwWindowShouldClose(window) == 0)
    {
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection;
        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        //model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 1000.0f);

        int modelLoc = glGetUniformLocation(shaderProgram, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        int viewLoc = glGetUniformLocation(shaderProgram, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        int perspectiveLoc = glGetUniformLocation(shaderProgram, "projection");
        glUniformMatrix4fv(perspectiveLoc, 1, GL_FALSE, glm::value_ptr(projection));


        // clear the window
        glClearColor(0.0f, 0.1f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        geometryBuffer.bindVertexArray();
        glDrawArrays(GL_TRIANGLES, 0, 3);
        geometryBuffer.unbindVertexArray();

        // swap buffer
        glfwSwapBuffers(window);

        // process user events
        glfwPollEvents();

        calculateFPS();
    }

    glfwTerminate();
}