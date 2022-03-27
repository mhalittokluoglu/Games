#include "Shader.hpp"
#include "Logger.hpp"
Shader::Shader(const char *shaderSource, uint32_t shaderType)
{
    int32_t success;
    char infoLog[512];
    m_ShaderID = glCreateShader(shaderType);
    glShaderSource(m_ShaderID, 1, &shaderSource, NULL);
    glCompileShader(m_ShaderID);
    glGetShaderiv(m_ShaderID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(m_ShaderID, 512, NULL, infoLog);
        Logger::LOG_ERROR("SHADER::%d::COMPILATION_FAILED:", m_ShaderID);
        Logger::LOG_ERROR(infoLog);
    }
}

Shader::~Shader()
{
    glDeleteShader(m_ShaderID);
}