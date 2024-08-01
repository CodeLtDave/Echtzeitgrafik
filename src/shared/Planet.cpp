#include "Planet.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>

Planet::Planet(const std::string& name, float rotationSpeed, float orbitSpeed, float distanceToSun, float size)
    : m_name(name), m_rotationSpeed(rotationSpeed), m_orbitSpeed(orbitSpeed), m_distanceToSun(distanceToSun), m_size(size) {}

void Planet::loadMesh(const std::filesystem::path& meshPath) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(meshPath.string(), aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }

    aiMesh* mesh = scene->mMeshes[0];
    std::vector<float> vertices;
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        vertices.push_back(mesh->mVertices[i].x * m_size);
        vertices.push_back(mesh->mVertices[i].y * m_size);
        vertices.push_back(mesh->mVertices[i].z * m_size);
        vertices.push_back(mesh->mNormals[i].x);
        vertices.push_back(mesh->mNormals[i].y);
        vertices.push_back(mesh->mNormals[i].z);
    }

    m_geometryBuffer.bindAndUploadBufferData(vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    m_geometryBuffer.setupAttributes();

    std::cout << "Mesh loaded for planet: " << m_name << std::endl;
}

void Planet::draw(GLint shaderProgram) {
    m_geometryBuffer.bindVertexArray();
    glDrawArrays(GL_TRIANGLES, 0, m_geometryBuffer.getVertexCount());
    m_geometryBuffer.unbindVertexArray();
}

const std::string& Planet::getName() const { return m_name; }
float Planet::getRotationSpeed() const { return m_rotationSpeed; }
float Planet::getOrbitSpeed() const { return m_orbitSpeed; }
float Planet::getDistanceToSun() const { return m_distanceToSun; }
float Planet::getSize() const { return m_size; }
