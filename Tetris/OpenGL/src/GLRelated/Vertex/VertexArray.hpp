#ifndef _VERTEXARRAY_HPP_
#define _VERTEXARRAY_HPP_
#include <inttypes.h>
class VertexArray
{
public:
    VertexArray();
    ~VertexArray();
    void Bind() const;
    void Unbind() const;

private:
    uint32_t m_VertexArrayId;
};
#endif