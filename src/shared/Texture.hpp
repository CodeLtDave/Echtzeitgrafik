#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>
#include <GL/glew.h>
#include <filesystem>

class Texture {
public:
    Texture(const std::filesystem::path& filePath);
    ~Texture();

    void bind(GLenum textureUnit = GL_TEXTURE0) const;
    void unbind() const;

    void setWrapping(GLenum s, GLenum t);
    void setFiltering(GLenum minFilter, GLenum magFilter);

private:
    GLuint m_textureID;
    GLenum m_target;
    int m_width, m_height, m_channels;

    void loadTexture(const std::filesystem::path& filePath);
};

#endif // TEXTURE_HPP
