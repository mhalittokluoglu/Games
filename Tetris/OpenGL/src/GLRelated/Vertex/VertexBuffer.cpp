#include "VertexBuffer.hpp"

VertexBuffer::VertexBuffer()
{
    glGenBuffers(1, &m_VertexId);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_VertexId);
}

void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexId);
}

void VertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::CopyData(float data[], uint32_t dataSize) const
{
    glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_DYNAMIC_DRAW);
}

void VertexBuffer::AddLayout(uint32_t layout, uint32_t vectSize,
                             uint32_t glType, bool glNormalized,
                             uint32_t stride, uint32_t offset)
{
    glVertexAttribPointer(layout, vectSize, glType, glNormalized, stride, (uint32_t *)(0));
    glEnableVertexAttribArray(layout);
}
