#ifndef _SHADERPROGRAM_HPP_
#define _SHADERPROGRAM_HPP_
#include "Shader.hpp"
#include "TetrisEngine/MathLib/TetrisMath.hpp"
class ShaderProgram
{
public:
    ShaderProgram();
    ~ShaderProgram();
    void AttachShader(const Shader &shader);
    void Link();
    void Use();
    void SetFloat3(const char *name, TetrisMath::Vec3 v);
    void SetColor(const char *name, TetrisMath::Color v);

private:
    uint32_t m_ProgramID;
};
#endif