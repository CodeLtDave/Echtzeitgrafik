#include "GeometryBuffer.hpp"

GeometryBuffer::GeometryBuffer()    //default contructor
    : m_vertexCount(0)
{
    //set vao, vbo and ebo to 1
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ebo);
}

GeometryBuffer::~GeometryBuffer()   //destructor
{
    //delete vao, vbo and ebo
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ebo);
}

GeometryBuffer::GeometryBuffer(GeometryBuffer&& other) noexcept     //move constructor
    //copy the vao, vbo and ebo from other to this
    : m_vao(other.m_vao), m_vbo(other.m_vbo), m_ebo(other.m_ebo), m_vertexCount(0)
{
    //set other vao, vbo and ebo to 0 to avoid double deletion
    other.m_vao = 0;
    other.m_vbo = 0;
    other.m_ebo = 0;
}

GeometryBuffer& GeometryBuffer::operator=(GeometryBuffer&& other) noexcept	//move assignment operator  
{
    //check if this is not the same as other
    if (this != &other)
    {
        //delete vao, vbo and ebo because they will be overwritten
        glDeleteVertexArrays(1, &m_vao);
        glDeleteBuffers(1, &m_vbo);
        glDeleteBuffers(1, &m_ebo);

        //copy the vao, vbo and ebo from other to this
        m_vao = other.m_vao;
        m_vbo = other.m_vbo;
        m_ebo = other.m_ebo;

        //set other vao, vbo and ebo to 0 to avoid double deletion
        other.m_vao = 0;
        other.m_vbo = 0;
        other.m_ebo = 0;
    }
    return *this;
}

void GeometryBuffer::bindAndUploadBufferData(GLsizeiptr size, const GLvoid* data, GLenum usage)
{
    //bind vao and vbo
    bindVertexArray();
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    //upload data to vbo
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);

    //unbind vao to avoid accidental changes
    unbindVertexArray();
}

void GeometryBuffer::bindVertexArray() const
{
    glBindVertexArray(this->m_vao);
}


void GeometryBuffer::unbindVertexArray() const
{
    //set vao to 0 effectively unbinding it to avoid accidental changes
	glBindVertexArray(0);
}

void GeometryBuffer::setupAttributes() {
    bindVertexArray();
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    unbindVertexArray();
}


GLsizei GeometryBuffer::getVertexCount() const
{
	return m_vertexCount;
}