#ifndef SHADER_HPP
#define SHADER_HPP

#include <GL/glew.h>
#include <filesystem>


std::string readShaderSource(const std::filesystem::path& shaderPath);
GLint createShaderPipeline(const std::filesystem::path& vertexShaderPath, const std::filesystem::path& fragmentShaderPath);
#endif
