#pragma once

#include <iostream>

#include <GL/glew.h> 
#include <GLFW/glfw3.h>


GLFWwindow* initAndCreateWindow(bool debugContext = false)
{
    GLFWwindow* window;  // created window

    if (glfwInit() == 0)
    {
        std::cerr << "GLFW failed to initiate." << std::endl;
    }
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, false);
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, debugContext);
    window = glfwCreateWindow(800, 600, "Echtzeitgrafik", nullptr, nullptr);

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