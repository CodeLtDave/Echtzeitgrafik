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

    SolarSystem(const SolarSystem& other);

    SolarSystem& operator=(const SolarSystem& other);

    SolarSystem(SolarSystem&& other) noexcept;

    SolarSystem& operator=(SolarSystem&& other) noexcept;

    void draw(Shader shader);
    void loadPlanets();

private:
    std::vector<Planet> m_planets;
    GeometryBuffer m_geometryBuffer;
};

#endif
