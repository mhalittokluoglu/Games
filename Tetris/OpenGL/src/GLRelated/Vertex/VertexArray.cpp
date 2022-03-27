#include "VertexArray.hpp"
#include "glad/glad.h"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &m_VertexArrayId);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_VertexArrayId);
}

void VertexArray::Bind() const
{
    glBindVertexArray(m_VertexArrayId);
}

void VertexArray::Unbind() const
{
    glBindVertexArray(0);
}