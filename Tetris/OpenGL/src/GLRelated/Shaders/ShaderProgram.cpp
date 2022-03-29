#include "ShaderProgram.hpp"
#include <cstdlib>
#include "Logger.hpp"

ShaderProgram::ShaderProgram()
{
    m_ProgramID = glCreateProgram();
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(m_ProgramID);
}

void ShaderProgram::AttachShader(const Shader &shader)
{
    glAttachShader(m_ProgramID, shader.m_ShaderID);
}

void ShaderProgram::Link()
{
    int32_t success;
    char infoLog[512] { 0 };
    glLinkProgram(m_ProgramID);
    glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &success);

    if (!success)
    {
        glGetProgramInfoLog(m_ProgramID, 512, NULL, infoLog);
        Logger::LOG_ERROR("SHADER::PROGRAM::LINKING_FAILED:");
        Logger::LOG_ERROR(infoLog);
    }
}

void ShaderProgram::Use()
{
    glUseProgram(m_ProgramID);
}


void ShaderProgram::SetFloat3(const char *name, TetrisMath::Vec3 v)
{
    glUniform3f(glGetUniformLocation(m_ProgramID, name), v.v1, v.v2, v.v3);
}

void ShaderProgram::SetColor(const char *name, TetrisMath::Color v)
{
    glUniform4f(glGetUniformLocation(m_ProgramID, name), v.R, v.G, v.B, v.A);
}
