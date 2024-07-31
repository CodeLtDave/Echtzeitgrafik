#ifndef POINTLIGHT_HPP
#define POINTLIGHT_HPP

#include <glm/glm.hpp>
#include <GL/glew.h>

class PointLight {
public:
    PointLight(const glm::vec3& position, const glm::vec3& color);

    void setPosition(const glm::vec3& position);
    void setColor(const glm::vec3& color);

    void apply(GLint shaderProgram);

private:
    glm::vec3 m_position;
    glm::vec3 m_color;
};

#endif // POINTLIGHT_HPP
