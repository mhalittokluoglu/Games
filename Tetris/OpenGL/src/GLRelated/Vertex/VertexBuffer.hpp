#ifndef _VERTEXBUFFER_HPP_
#define _VERTEXBUFFER_HPP_
#include "glad/glad.h"
#include <inttypes.h>
class VertexBuffer
{
public:
    VertexBuffer();
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;
    void CopyData(float data[], uint32_t dataSize) const;
    void AddLayout(uint32_t layout, uint32_t vectSize = 3,
        uint32_t glType = GL_FLOAT, bool glNormalized = false,
        uint32_t stride = (3 * sizeof(float)), uint32_t offset = 0);
    
private:
    uint32_t m_VertexId;

};
#endif