#include "PointLight.hpp"
#include "Shader.hpp"

PointLight::PointLight(const glm::vec3& position, const glm::vec3& color)
    : m_position(position), m_color(color) {}

void PointLight::setPosition(const glm::vec3& position) {
    m_position = position;
}

void PointLight::setColor(const glm::vec3& color) {
    m_color = color;
}

void PointLight::apply(Shader shader) {
    GLint lightPosLoc = shader.getLocation("lightPos");
    GLint lightColorLoc = shader.getLocation("lightColor");

    shader.setUniform(lightPosLoc, m_position);
    shader.setUniform(lightColorLoc, m_color);
}
