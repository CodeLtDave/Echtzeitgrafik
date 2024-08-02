#ifndef PLANET_HPP
#define PLANET_HPP

#include <string>
#include <glm/glm.hpp>
#include "GeometryBuffer.hpp"
#include <filesystem>
#include "Texture.hpp"

class Planet {
public:
    Planet(const std::string& name, float rotationSpeed, float orbitSpeed, float distanceToSun, float size);

    void loadMesh(const std::filesystem::path& meshPath);
    void loadTexture();
    void draw(GLint shaderProgram);

    const std::string& getName() const;
    float getRotationSpeed() const;
    float getOrbitSpeed() const;
    float getDistanceToSun() const;
    float getSize() const;

private:
    std::string m_name;
    float m_rotationSpeed;
    float m_orbitSpeed;
    float m_distanceToSun;
    float m_size;
    Texture* m_texture;
    GeometryBuffer m_geometryBuffer;
};

#endif
