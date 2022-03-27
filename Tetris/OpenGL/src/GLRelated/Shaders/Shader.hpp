#ifndef _SHADER_HPP_
#define _SHADER_HPP_
#include <inttypes.h>
#include "glad/glad.h"
#include "GLRelated/MatData.hpp"

class ShaderProgram;
class Shader
{
public:
    Shader(const char *shaderSource, uint32_t shaderType);
    ~Shader();

    inline uint32_t GetShaderID() { return m_ShaderID;}
    friend class ShaderProgram;
private:
    uint32_t m_ShaderID;
};
#endif