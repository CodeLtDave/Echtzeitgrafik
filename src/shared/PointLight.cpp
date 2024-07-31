#include "PointLight.hpp"

PointLight::PointLight(const glm::vec3& position, const glm::vec3& color)
    : m_position(position), m_color(color) {}

void PointLight::setPosition(const glm::vec3& position) {
    m_position = position;
}

void PointLight::setColor(const glm::vec3& color) {
    m_color = color;
}

void PointLight::apply(GLint shaderProgram) {
    GLint lightPosLoc = glGetUniformLocation(shaderProgram, "lightPos");
    GLint lightColorLoc = glGetUniformLocation(shaderProgram, "lightColor");

    glUniform3f(lightPosLoc, m_position.x, m_position.y, m_position.z);
    glUniform3f(lightColorLoc, m_color.r, m_color.g, m_color.b);
}
