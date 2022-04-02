#include "Rectangle.hpp"
#include <cstring>

using namespace TetrisShapes;
uint32_t TetrisShapes::Rectangle::s_Indices[6] = {0,1,2,1,2,3};

Rectangle::Rectangle()
{
    memset(m_Data, 0, sizeof(m_Data));
    UpdateData();
    m_ShaderProgram = nullptr;
}
Rectangle::~Rectangle()
{
}

Rectangle::Rectangle(TetrisMath::GLPosition position, TetrisMath::Color color)
    : Position{position}, Color{color}
{
    memset(m_Data, 0, sizeof(m_Data));
    UpdateData();
    m_ShaderProgram = nullptr;
}

void Rectangle::Initialize(ShaderProgram *shaderProgram)
{
    m_ShaderProgram = shaderProgram;
    m_Vao.Bind();
    m_Ebo.Bind();
    m_Ebo.CopyData(s_Indices, sizeof(s_Indices));
    UpdateData();
    CopyUpdatedData();
    m_Vbo.AddLayout(0);
    m_Vbo.Unbind();
    m_Vao.Unbind();
    m_Ebo.Unbind();
}

void Rectangle::Draw()
{
    m_Vao.Bind();
    m_Vbo.Bind();
    m_ShaderProgram->SetColor("shapeColor", Color);
    glDrawElements(GL_TRIANGLES, sizeof(s_Indices) / sizeof(uint32_t), GL_UNSIGNED_INT, 0);
}

void Rectangle::UpdateData()
{
    UpdateData(Position.X, Position.Y, Position.s_Width, Position.s_Height);
}

void Rectangle::SetBorderData(float offsetX, float offsetY)
{
    UpdateData(Position.X, Position.Y, offsetX, offsetY);
}

void Rectangle::CopyUpdatedData()
{
    m_Vao.Bind();
    m_Vbo.Bind();
    m_Vbo.CopyData(m_Data, sizeof(m_Data));
}

void Rectangle::UpdateData(float X, float Y, float xoff, float yoff)
{
    m_Data[0] = X;          m_Data[1] = Y + yoff;   m_Data[2] = 0.0f;
    m_Data[3] = X + xoff;   m_Data[4] = Y + yoff;   m_Data[5] = 0.0f;
    m_Data[6] = X;          m_Data[7] = Y;          m_Data[8] = 0.0f;
    m_Data[9] = X + xoff;   m_Data[10] = Y;         m_Data[11] = 0.0f;
}