#include "SolarSystem.hpp"
#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include "planetData.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>


SolarSystem::SolarSystem() {
    loadPlanets();
}

SolarSystem::~SolarSystem() {}


void SolarSystem::draw(GLint shaderProgram) {
    float time = 0.5f * glfwGetTime();
    for (auto& planet : m_planets) {
        // Rotation around the sun
        glm::mat4 model = glm::rotate(glm::mat4(1.0f), time * glm::radians(planet.getOrbitSpeed()), glm::vec3(0.0f, 1.0f, 0.0f));

        // Distance to the sun
        model = glm::translate(model, glm::vec3(planet.getDistanceToSun(), 0.0f, 0.0f));

        // Rotation around its own axis
        model = glm::rotate(model, time * glm::radians(planet.getRotationSpeed()), glm::vec3(0.0f, 1.0f, 0.0f));

        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
        planet.m_geometryBuffer.m_vertexCount = 32512;
        planet.draw(shaderProgram);
    }
}

void SolarSystem::loadPlanets() {
    for (const auto& data : planetData) {
        m_planets.emplace_back(data.name, data.rotationSpeed, data.orbitSpeed, data.distanceToSun, data.size);
    }

    for (auto& planet : m_planets) {
        planet.loadMesh(SPHERE_PATH); // Pfad zum Mesh anpassen
    }
}
