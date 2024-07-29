#pragma once

#include <GL/glew.h> // has to be included first!
#include <glm/glm.hpp>

using namespace glm;
enum Shaders { 
	Vertex, 
	Geometry, 
	Fragment,
	Compute 
};

class Shader {
	//Constructor and Destructor;
	Shader(const char* source_1, const char* source_2, Shaders shader_1, Shader shader_2);
	~Shader();

	//methods to use and delete shader
	void use();
	void stop();


	//Uniforms
	void setUniform(GLint location, int value);	void setUniform(GLint location, float value);	void setUniform(GLint location, vec3 value);	void setUniform(GLint location, vec4 value);	void setUniform(GLint location, mat4 value);
	GLint createShaderPipeline(const char* source_1, const char* source_2);
};

//Helpfull functions
void compileShader(GLint shader);
bool isShaderReady(GLint shader, int status, GLint& success);
GLint createShader(const char* source, int shader);

