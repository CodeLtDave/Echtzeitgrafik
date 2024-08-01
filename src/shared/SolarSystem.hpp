#ifndef SOLARSYSTEM_HPP
#define SOLARSYSTEM_HPP

#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include "GeometryBuffer.hpp"
#include <filesystem>

class SolarSystem {
public:
    SolarSystem(const std::filesystem::path& spherePath);
    ~SolarSystem();
    void draw(GLint shaderProgram);

private:
    GeometryBuffer m_geometryBuffer;
    void loadSphere(const std::filesystem::path& spherePath);
};

#endif // SOLARSYSTEM_HPP
