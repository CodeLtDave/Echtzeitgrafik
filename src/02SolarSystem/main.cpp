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
#include <shared/matrixData.h>
#include <glm/ext/matrix_clip_space.hpp>

class SolarSystemSimulation {
public:
    SolarSystemSimulation() {
        std::cout << "Hello SolarSystemSimulation!" << std::endl;

        window = initAndCreateWindow();
        shader = new Shader(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);
        solarSystem = new SolarSystem();

        initializeScene();
    }

    ~SolarSystemSimulation() {
        delete shader;
        delete solarSystem;
    }

    void run() {
        while (glfwWindowShouldClose(window) == 0) {
            // clear the window
            glClearColor(0.0f, 0.1f, 0.2f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // Zeichne die Planeten
            solarSystem->draw(*shader);

            // swap buffer
            glfwSwapBuffers(window);

            // process user events
            glfwPollEvents();

            calculateFPS();
             
            // Check for OpenGL errors
            GLenum error = glGetError();
            if (error != GL_NO_ERROR) {
                std::cerr << "OpenGL Error: " << error << std::endl;
            }
        }
        glfwTerminate();
    }



private:
    GLFWwindow* window;
    Shader* shader;
    SolarSystem* solarSystem;
    bool projectionIsPerspective = true;

    void initializeScene()
    {
        // Set the viewport
        glViewport(0, 0, windowWidth, windowHeight);

        // Set callback functions for keyboard ("space") input
        glfwSetWindowUserPointer(window, this);
        glfwSetKeyCallback(window, SolarSystemSimulation::spaceBarPressed);

        // Create and Initialize Point Light
        PointLight pointLight(glm::vec3(1.2f, 1.0f, 2.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        pointLight.apply(*shader);

        // set the shader
        GLint viewPosLoc = shader->getLocation("viewPos");
        shader->setUniform(viewPosLoc, viewPosVec);
        GLint viewLoc = shader->getLocation("view");
        shader->setUniform(viewLoc, viewMatrix);
        GLint modelLoc = shader->getLocation("model");
        shader->setUniform(modelLoc, modelMatrix);
        GLint projLoc = shader->getLocation("projection");
        shader->setUniform(projLoc, projectionMatrix);

        // Enable depth test
        glEnable(GL_DEPTH_TEST);
    }

    void swapPerspective() {
        if (projectionIsPerspective) {
            std::cout << "Orthogonal Projection" << std::endl;
            projectionIsPerspective = false;
            projectionMatrix = glm::ortho(-windowWidth / (2 * 100), windowWidth / (2 * 100), -windowHeight / (2 * 100), windowHeight / (2 * 100), 0.1f, 1000.0f);
        }
        else {
            std::cout << "Perspective Projection" << std::endl;
            projectionIsPerspective = true;
            projectionMatrix = glm::perspective(glm::radians(45.0f), windowWidth / windowHeight, 0.1f, 1000.0f);
        }
        GLint projLoc = shader->getLocation("projection");
        shader->setUniform(projLoc, projectionMatrix);
	}

    static void spaceBarPressed(GLFWwindow* window, int key, int scancode, int action, int mods) {
        if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
            SolarSystemSimulation* simulation = static_cast<SolarSystemSimulation*>(glfwGetWindowUserPointer(window));
            if (simulation) {
                simulation->swapPerspective();
            }
        }
    }
};

int main(int argc, char** argv)
{    
    // Aktiviere Speicherleck-Erkennung
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

 
    SolarSystemSimulation simulation;
    simulation.run();

    _CrtDumpMemoryLeaks();
    return 0;
}
