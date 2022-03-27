#ifndef _ELEMENTBUFFER_HPP_
#define _ELEMENTBUFFER_HPP_
#include "glad/glad.h"
#include <inttypes.h>
class ElementBuffer
{
public:
    ElementBuffer();
    ~ElementBuffer();
    void Bind() const;
    void Unbind() const;
    void CopyData(uint32_t indices[], uint32_t size);

private:
    uint32_t m_ElementId;
};
#endif