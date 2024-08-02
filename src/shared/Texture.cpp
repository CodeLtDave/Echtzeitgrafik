#include "Texture.hpp"
#include <stb_image.h>
#include <iostream>
#include <stdexcept>

Texture::Texture(const std::filesystem::path& filePath)
    : m_target(GL_TEXTURE_2D), m_textureID(0), m_width(0), m_height(0), m_channels(0) {
    glGenTextures(1, &m_textureID);
    loadTexture(filePath);
}

Texture::~Texture() {
    glDeleteTextures(1, &m_textureID);
}

void Texture::bind(GLenum textureUnit) const {
    glActiveTexture(textureUnit);
    glBindTexture(m_target, m_textureID);
}

void Texture::unbind() const {
    glBindTexture(m_target, 0);
}

void Texture::setWrapping(GLenum s, GLenum t) {
    bind();
    glTexParameteri(m_target, GL_TEXTURE_WRAP_S, s);
    glTexParameteri(m_target, GL_TEXTURE_WRAP_T, t);
    unbind();
}

void Texture::setFiltering(GLenum minFilter, GLenum magFilter) {
    bind();
    glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, magFilter);
    unbind();
}

void Texture::loadTexture(const std::filesystem::path& filePath) {
    stbi_set_flip_vertically_on_load(false);
    unsigned char* data = stbi_load(filePath.string().c_str(), &m_width, &m_height, &m_channels, 0);
    if (!data) {
        throw std::runtime_error("Failed to load texture: " + filePath.string());
    }

    bind();
    GLenum format = (m_channels == 4) ? GL_RGBA : GL_RGB;
    glTexImage2D(m_target, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(m_target);
    unbind();
    stbi_image_free(data);
}
