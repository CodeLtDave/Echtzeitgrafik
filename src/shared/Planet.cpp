#include "Planet.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include "data.h"
#include "Shader.hpp"

Planet::Planet(const std::string& name, float rotationSpeed, float orbitSpeed, float distanceToSun, float size)
    : m_name(name), m_rotationSpeed(rotationSpeed), m_orbitSpeed(orbitSpeed), m_distanceToSun(distanceToSun), m_size(size), m_texture(nullptr) {}

Planet::Planet(const Planet& other)
    : m_name(other.m_name), m_rotationSpeed(other.m_rotationSpeed), m_orbitSpeed(other.m_orbitSpeed), m_distanceToSun(other.m_distanceToSun), m_size(other.m_size), m_texture(nullptr)
{
}

Planet::Planet(Planet&& other) noexcept
    : m_name(std::move(other.m_name)), m_rotationSpeed(other.m_rotationSpeed), m_orbitSpeed(other.m_orbitSpeed), m_distanceToSun(other.m_distanceToSun), m_size(other.m_size), m_texture(other.m_texture)
{
    other.m_texture = nullptr;
}

Planet& Planet::operator=(const Planet& other)
{
    if (this == &other) {
        return *this;
    }

    m_name = other.m_name;
    m_rotationSpeed = other.m_rotationSpeed;
    m_orbitSpeed = other.m_orbitSpeed;
    m_distanceToSun = other.m_distanceToSun;
    m_size = other.m_size;

    if (m_texture) {
        delete m_texture;
    }
    m_texture = nullptr;

    return *this;
}

Planet& Planet::operator=(Planet&& other) noexcept
{
    if (this == &other) {
        return *this;
    }

    m_name = std::move(other.m_name);
    m_rotationSpeed = other.m_rotationSpeed;
    m_orbitSpeed = other.m_orbitSpeed;
    m_distanceToSun = other.m_distanceToSun;
    m_size = other.m_size;

    if (m_texture) {
        delete m_texture;
    }
    m_texture = other.m_texture;
    other.m_texture = nullptr;

    return *this;
}

Planet::~Planet()
{
    delete m_texture;
}

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
        if (mesh->mTextureCoords[0]) {
            vertices.push_back(mesh->mTextureCoords[0][i].x);
            vertices.push_back(mesh->mTextureCoords[0][i].y);
            vertices.push_back(1.0f);
        }
        else {
            vertices.push_back(0.0f);
            vertices.push_back(0.0f);
        }
    }

    std::vector<uint32_t> indices;
    for( unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    m_geometryBuffer.bindAndUploadBufferData(vertices.size() * sizeof(float), vertices.data(), indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);
    m_geometryBuffer.setupAttributes();
    std::cout << "Mesh loaded for planet: " << m_name << std::endl;
}

void Planet::loadTexture() {
    std::filesystem::path texturePath = PLANET_TEXTURE_PATH / ("2k_" + m_name + ".jpg");
    m_texture = new Texture(texturePath);
    std::cout << "Texture loaded for planet: " << m_name << std::endl;
}

void Planet::draw() {
    m_texture->bind();
    m_geometryBuffer.draw();
    m_texture->unbind();
}

const std::string& Planet::getName() const { return m_name; }
float Planet::getRotationSpeed() const { return m_rotationSpeed; }
float Planet::getOrbitSpeed() const { return m_orbitSpeed; }
float Planet::getDistanceToSun() const { return m_distanceToSun; }
float Planet::getSize() const { return m_size; }
