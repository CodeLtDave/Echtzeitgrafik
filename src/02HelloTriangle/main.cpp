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
#include "shared/SolarSystem.hpp"

class SolarSystemSimulation {
public:
    SolarSystemSimulation() {
        std::cout << "Hello SolarSystemSimulation!" << std::endl;
        window = initAndCreateWindow();
        shaderProgram = createShaderPipeline(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);
        glfwSetWindowUserPointer(window, this);
        glfwSetKeyCallback(window, SolarSystemSimulation::spaceBarPressed);

        // SolarSystem initialisieren
        solarSystem = new SolarSystem();
    }

    ~SolarSystemSimulation() {
        delete solarSystem;
    }

    void run() {
        glViewport(0, 0, windowWidth, windowHeight);

        glUseProgram(shaderProgram);

        // Create and Initialize Point Light
        PointLight pointLight(glm::vec3(1.2f, 1.0f, 2.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        pointLight.apply(shaderProgram);

        setUniforms(shaderProgram);

        glEnable(GL_DEPTH_TEST);

        while (glfwWindowShouldClose(window) == 0) {
            //setContinousUniforms(shaderProgram);

            // clear the window
            glClearColor(0.0f, 0.1f, 0.2f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // Zeichne die Planeten
            solarSystem->draw(shaderProgram);

            // swap buffer
            glfwSwapBuffers(window);

            // process user events
            glfwPollEvents();

            calculateFPS();

            GLenum error = glGetError();
            if (error != GL_NO_ERROR) {
                std::cerr << "OpenGL Error: " << error << std::endl;
            }
        }

        glfwTerminate();
    }

private:
    GLFWwindow* window;
    GLint shaderProgram;
    SolarSystem* solarSystem;

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
