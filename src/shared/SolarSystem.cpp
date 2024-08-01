#include "SolarSystem.hpp"
#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include "planetData.h"


SolarSystem::SolarSystem() {
    loadPlanets();
}

SolarSystem::~SolarSystem() {}


void SolarSystem::draw(GLint shaderProgram) {
    for (auto& planet : m_planets) {
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
