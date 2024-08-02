#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <filesystem>
#include <string>


class Shader {
public:
	Shader();
	Shader(const std::filesystem::path& vertexShaderPath, const std::filesystem::path& fragmentShaderPath);
	void createShaderProgram(const std::filesystem::path& vertexShaderPath, const std::filesystem::path& fragmentShaderPath);
	std::string readShaderSource(const std::filesystem::path& shaderPath);

	GLint getLocation(const char* uniformName);
	void setUniform(GLint location, glm::mat4 matrix);
	void setUniform(GLint location, glm::vec3 value);

private:
	GLint m_shaderProgram;
};
