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
#include "shared/PointLight.hpp"

class SolarSystemSimulation {
public:
    SolarSystemSimulation() {
        std::cout << "Hello SolarSystemSimulation!" << std::endl;
        window = initAndCreateWindow();
        shaderProgram = createShaderPipeline(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);
        glfwSetWindowUserPointer(window, this);
        glfwSetKeyCallback(window, SolarSystemSimulation::spaceBarPressed);
    }

    void run() {
        glViewport(0, 0, 800, 600);

        GeometryBuffer geometryBuffer;
        geometryBuffer.bindAndUploadBufferData(sizeof(cube), cube, GL_STATIC_DRAW);

        /* Position attribute */
        geometryBuffer.bindVertexArray();
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);

        /* Color attribute */
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        /* Normal Vector attribute (for light calculation)  */
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(2);

        geometryBuffer.unbindVertexArray();

        glUseProgram(shaderProgram);

        // Create and Initialize Point Light
        PointLight pointLight(glm::vec3(1.2f, 1.0f, 2.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        pointLight.apply(shaderProgram);

        // Uniform Locations
        GLint viewPosLoc = glGetUniformLocation(shaderProgram, "viewPos");
        GLint objColorLoc = glGetUniformLocation(shaderProgram, "objColor");

        // Uniform Werte setzen
        glUniform3f(viewPosLoc, 0.0f, 0.0f, 3.0f);
        glUniform3f(objColorLoc, 0.78f, 0.66f, 0.46f);
        glPolygonMode(GL_FRONT_AND_BACK, GL_TRIANGLES);

        setShaderUniforms(shaderProgram);

        glEnable(GL_DEPTH_TEST);

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

private:
    GLFWwindow* window;
    GLint shaderProgram;

    static void spaceBarPressed(GLFWwindow* window, int key, int scancode, int action, int mods) {
        if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
            SolarSystemSimulation* simulation = static_cast<SolarSystemSimulation*>(glfwGetWindowUserPointer(window));
            if (simulation) {
                std::cout << "Space Bar Pressed" << std::endl;
                swapPerspective(simulation->shaderProgram);
            }
        }
    }
};

int main(int argc, char** argv) 
{
    SolarSystemSimulation simulation;
    simulation.run();

    return 0;
}
