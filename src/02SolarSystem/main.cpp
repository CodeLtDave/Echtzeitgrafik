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
#include <glm/gtx/string_cast.hpp>

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
    const float moveSpeed = 0.5f;

    void initializeScene()
    {
        // Set the viewport
        glViewport(0, 0, windowWidth, windowHeight);

        // Set callback functions for keyboard ("space") input
        glfwSetWindowUserPointer(window, this);
        glfwSetKeyCallback(window, SolarSystemSimulation::keyCallback);

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

    void adjustViewPos(int mult, char axis) {
        if (axis == 'z') {
            viewPosVec.z += moveSpeed * mult;
        }
        else if (axis == 'y') {
            viewPosVec.y += moveSpeed * mult;
        }
        else if (axis == 'x') {
            viewPosVec.x += moveSpeed * mult;
        }
        viewMatrix = glm::lookAt(viewPosVec, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        GLint viewLoc = shader->getLocation("view");
        shader->setUniform(viewLoc, viewMatrix);
        std::cout << "viewPos adjusted: " << glm::to_string(viewPosVec) << std::endl;
    }


    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        SolarSystemSimulation* simulation = static_cast<SolarSystemSimulation*>(glfwGetWindowUserPointer(window));
        if (simulation) {
            if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
                std::cout << "Space Bar Pressed" << std::endl;
                simulation->swapPerspective();
            }
            else if ((key == GLFW_KEY_W || key == GLFW_KEY_S || key == GLFW_KEY_A || key == GLFW_KEY_D || key == GLFW_KEY_Q || key == GLFW_KEY_E) &&
                (action == GLFW_PRESS || action == GLFW_REPEAT)) {
                switch (key) {
                case GLFW_KEY_W:
                    simulation->adjustViewPos(1, 'y');
                    break;
                case GLFW_KEY_S:
                    simulation->adjustViewPos(-1, 'y');
                    break;
                case GLFW_KEY_A:
                    simulation->adjustViewPos(1, 'x');
                    break;
                case GLFW_KEY_D:
                    simulation->adjustViewPos(-1, 'x');
                    break;
                case GLFW_KEY_Q:
                    simulation->adjustViewPos(1, 'z');
                    break;
                case GLFW_KEY_E:
                    simulation->adjustViewPos(-1, 'z');
                    break;
                }
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
