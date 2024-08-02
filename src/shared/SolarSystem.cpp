#include "SolarSystem.hpp"
#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include "planetData.h"
#include <GLFW/glfw3.h>
#include "Shader.hpp"
#include "matrixData.h"

SolarSystem::SolarSystem() {
    loadPlanets();
}

SolarSystem::~SolarSystem() {
    m_planets.clear();
}

// Rule of Five: Copy Constructor
SolarSystem::SolarSystem(const SolarSystem& other) : m_planets(other.m_planets) {}

// Rule of Five: Copy Assignment Operator
SolarSystem& SolarSystem::operator=(const SolarSystem& other) {
    if (this == &other) return *this;
    m_planets = other.m_planets;
    return *this;
}

// Rule of Five: Move Constructor
SolarSystem::SolarSystem(SolarSystem&& other) noexcept : m_planets(std::move(other.m_planets)) {}

// Rule of Five: Move Assignment Operator
SolarSystem& SolarSystem::operator=(SolarSystem&& other) noexcept {
    if (this == &other) return *this;
    m_planets = std::move(other.m_planets);
    return *this;
}

void SolarSystem::draw(Shader shader) {
    float time = 0.5f * glfwGetTime();
    for (auto& planet : m_planets) {
        // Rotation around the sun
        glm::mat4 model = glm::rotate(glm::mat4(1.0f), time * glm::radians(planet.getOrbitSpeed()), glm::vec3(0.0f, 1.0f, 0.0f));

        // Distance to the sun
        model = glm::translate(model, glm::vec3(planet.getDistanceToSun(), 0.0f, 0.0f));

        // Rotation around its own axis
        model = glm::rotate(model, time * glm::radians(500000/planet.getRotationSpeed()), glm::vec3(0.0f, 1.0f, 0.0f));

        GLint emissionLoc = shader.getLocation("emission");
        if (planet.getName() == "sun") {
            shader.setUniform(emissionLoc, emissionSunVec);
        }
        else {
            shader.setUniform(emissionLoc, emissionPlanetVec);
        }
        GLint modelLoc = shader.getLocation("model");
        shader.setUniform(modelLoc, model);
        planet.draw();
    }
}

void SolarSystem::loadPlanets() {
    for (const auto& data : planetData) {
        m_planets.emplace_back(data.name, data.rotationSpeed, data.orbitSpeed, data.distanceToSun, data.size);
    }

    for (auto& planet : m_planets) {
        planet.loadTexture();
        planet.loadMesh(SPHERE_PATH); // Pfad zum Mesh anpassen
    }
}
