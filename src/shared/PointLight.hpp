#ifndef POINTLIGHT_HPP
#define POINTLIGHT_HPP

#include <glm/glm.hpp>
#include <GL/glew.h>
#include "Shader.hpp"

class PointLight {
public:
    PointLight(const glm::vec3& position, const glm::vec3& color);

    void setPosition(const glm::vec3& position);
    void setColor(const glm::vec3& color);

    void apply(Shader shader);

private:
    glm::vec3 m_position;
    glm::vec3 m_color;
};

#endif
