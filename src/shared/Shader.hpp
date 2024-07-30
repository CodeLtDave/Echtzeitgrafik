#ifndef SHADER_HPP
#define SHADER_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <filesystem>

static bool projectionIsPerspective = true;

std::string readShaderSource(const std::filesystem::path& shaderPath);
GLint createShaderPipeline(const std::filesystem::path& vertexShaderPath, const std::filesystem::path& fragmentShaderPath);
void setShaderUniforms(GLint shaderProgram);	
void setContinousUniforms(GLint shaderProgram);
void swapPerspective(GLint shaderProgram);

void setUniform(GLint location, int value);
void setUniform(GLint location, float value);
void setUniform(GLint location, glm::vec3 value);
void setUniform(GLint location, glm::vec4 value);
void setUniform(GLint location, glm::mat4 value);

#endif
