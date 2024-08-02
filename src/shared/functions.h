#pragma once

#include <iostream>

#include <GL/glew.h> 
#include <GLFW/glfw3.h>
#include "data.h"
#include <stb_image.h>


GLFWwindow* initAndCreateWindow(bool debugContext = false)
{
    GLFWwindow* window;  // created window

    if (glfwInit() == 0)
    {
        std::cerr << "GLFW failed to initiate." << std::endl;
    }
    glfwWindowHint(GLFW_RESIZABLE, false);
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, debugContext);
    window = glfwCreateWindow(windowWidth, windowHeight, "Echtzeitgrafik", nullptr, nullptr);

    // check if window was created successfully
    if (window == nullptr)
    {
        std::cerr << "GLFW failed to create window." << std::endl;
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "GLFW failed to create window." << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    int flags; glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
    {
        // initialize debug output 
        auto debugCallback = [](
            GLenum source, GLenum type, GLuint id, GLenum severity,
            GLsizei messageLength, const GLchar* message, const void* userParam)
            {
                std::cerr << "[OpenGL] " << id << ": " << message << std::endl;
            };
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(debugCallback, nullptr);
    }
    glEnable(GL_MULTISAMPLE);

    return window;
}

static double lastTime = glfwGetTime();
void calculateFPS()
{
	static int nbFrames = 0;
	double currentTime = glfwGetTime();
	nbFrames++;
	if (currentTime - lastTime >= 1.0)
	{
		std::cout << "FPS: " << double(nbFrames) << std::endl;
		nbFrames = 0;
		lastTime += 1.0;
	}
}