// Shader.hpp
#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
    Shader(const GLchar* vertexSource, const GLchar* fragmentSource);
    ~Shader();

    void use() const;
    void setUniform(GLint location, int value) const;
    void setUniform(GLint location, float value) const;
    void setUniform(GLint location, const glm::vec3& value) const;
    void setUniform(GLint location, const glm::vec4& value) const;
    void setUniform(GLint location, const glm::mat4& value) const;

private:
    GLuint programID;
    GLuint compileShader(const GLchar* source, GLenum shaderType) const;
    void linkProgram(GLuint vertexShader, GLuint fragmentShader);
};

#endif // SHADER_HPP
