#pragma once

#include <GL/glew.h>

class GeometryBuffer
{
public:
    GeometryBuffer();   //default constructor
    ~GeometryBuffer();  //destructor

    GeometryBuffer(const GeometryBuffer& other) = delete;   //copy constructor
    GeometryBuffer& operator=(const GeometryBuffer& other) = delete;    //copy assignment operator

    GeometryBuffer(GeometryBuffer&& other) noexcept;  //move constructor
    GeometryBuffer& operator=(GeometryBuffer&& other) noexcept;   //move assignment operator

    void GeometryBuffer::bindAndUploadBufferData(GLsizeiptr vertexSize, const GLvoid* vertexData, GLsizeiptr indiceSize, const GLvoid* indiceData, GLenum usage);
    void bindVertexArray() const;
    void unbindVertexArray() const;
    GLuint getVao() const { return m_vao; }
    void GeometryBuffer::setupAttributes();

    void draw();

    

private:
    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_ebo;
    int indiceCount;
};
