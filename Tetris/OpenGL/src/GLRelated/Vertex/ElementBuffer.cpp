#include "ElementBuffer.hpp"

ElementBuffer::ElementBuffer()
{
    glGenBuffers(1, &m_ElementId);
}

ElementBuffer::~ElementBuffer()
{
    glDeleteBuffers(1, &m_ElementId);
}

void ElementBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ElementId);
}

void ElementBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void ElementBuffer::CopyData(uint32_t indices[], uint32_t indicesSize) const
{
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize * sizeof(uint32_t), indices, GL_DYNAMIC_DRAW);
}
