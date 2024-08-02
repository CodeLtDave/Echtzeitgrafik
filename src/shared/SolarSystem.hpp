#ifndef SOLARSYSTEM_HPP
#define SOLARSYSTEM_HPP

#include <vector>
#include <filesystem>
#include "Planet.hpp"
#include "Shader.hpp"

class SolarSystem {
public:
    SolarSystem();
    ~SolarSystem();

    void draw(Shader shader);
    void loadPlanets();

private:
    std::vector<Planet> m_planets;
    GeometryBuffer m_geometryBuffer;
};

#endif
