#ifndef _SHADERPROGRAM_HPP_
#define _SHADERPROGRAM_HPP_
#include "Shader.hpp"
class ShaderProgram
{
public:
    ShaderProgram();
    ~ShaderProgram();
    void AttachShader(const Shader &shader);
    void Link();
    void Use();
    void SetFloat3(const char *name, Vect3 v);

private:
    uint32_t m_ProgramID;
};
#endif