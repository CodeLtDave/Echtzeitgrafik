#include "SolarSystem.hpp"
#include <iostream>

SolarSystem::SolarSystem(const std::filesystem::path& spherePath) {
    loadSphere(spherePath);
}

SolarSystem::~SolarSystem() {}

void SolarSystem::loadSphere(const std::filesystem::path& spherePath) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(spherePath.string(), aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }

    aiMesh* mesh = scene->mMeshes[0];
    std::vector<float> vertices;
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        vertices.push_back(mesh->mVertices[i].x);
        vertices.push_back(mesh->mVertices[i].y);
        vertices.push_back(mesh->mVertices[i].z);
        vertices.push_back(mesh->mNormals[i].x);
        vertices.push_back(mesh->mNormals[i].y);
        vertices.push_back(mesh->mNormals[i].z);
    }

    m_geometryBuffer.bindAndUploadBufferData(vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    m_geometryBuffer.setupAttributes();

    // Setzen Sie die Anzahl der Vertices
    m_geometryBuffer.m_vertexCount = mesh->mNumVertices;
    std::cout << "Vertex Count: " << m_geometryBuffer.m_vertexCount << std::endl;
}


void SolarSystem::draw(GLint shaderProgram) {
    m_geometryBuffer.bindVertexArray();

    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL error before glDrawArrays: " << err << std::endl;
    }

    glDrawArrays(GL_TRIANGLES, 0, m_geometryBuffer.getVertexCount());

    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL error after glDrawArrays: " << err << std::endl;
    }

    m_geometryBuffer.unbindVertexArray();
}
