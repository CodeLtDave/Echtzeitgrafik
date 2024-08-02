#pragma once

#include <filesystem>
#include <GL/glew.h>

class Texture {
public:
    Texture(const std::filesystem::path& filePath);
    ~Texture();

    Texture(const Texture& other); // Kopierkonstruktor
    Texture& operator=(const Texture& other); // Kopierzuweisungsoperator
    Texture(Texture&& other) noexcept; // Move-Konstruktor
    Texture& operator=(Texture&& other) noexcept; // Move-Zuweisungsoperator

    void bind(GLenum textureUnit = GL_TEXTURE0) const;
    void unbind() const;
    void setWrapping(GLenum s, GLenum t);
    void setFiltering(GLenum minFilter, GLenum magFilter);
    void loadTexture(const std::filesystem::path& filePath);

private:
    void release();

    GLenum m_target;
    GLuint m_textureID;
    int m_width;
    int m_height;
    int m_channels;
};

