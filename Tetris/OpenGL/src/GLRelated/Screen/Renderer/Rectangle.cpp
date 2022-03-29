#include "Rectangle.hpp"
#include <cstring>


std::array<uint32_t,6> Rectangle::s_Indices = {0,1,2,1,2,3};

Rectangle::Rectangle()
{
    m_Data.fill(0.0f);
    UpdateData();
    m_ShaderProgram = nullptr;
}
Rectangle::~Rectangle()
{
}

Rectangle::Rectangle(TetrisMath::GLPosition position, TetrisMath::Color color)
    : Position{position}, Color{color}
{
    m_Data.fill(0.0f);
    UpdateData();
    m_ShaderProgram = nullptr;
}

void Rectangle::Initialize(ShaderProgram *shaderProgram)
{
    m_ShaderProgram = shaderProgram;
    m_Vao.Bind();
    m_Ebo.Bind();
    m_Ebo.CopyData(s_Indices.begin(), s_Indices.size());
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
    glDrawElements(GL_TRIANGLES, s_Indices.size(), GL_UNSIGNED_INT, 0);
}

void Rectangle::UpdateData()
{
    m_Data = {
        Position.X, Position.Y + Position.s_Height, 0.0f,
        Position.X + Position.s_Width, Position.Y + Position.s_Height, 0.0f,
        Position.X, Position.Y, 0.0f,
        Position.X + Position.s_Width, Position.Y, 0.0f};
}

void Rectangle::SetBorderData(float offsetX, float offsetY)
{
    m_Data = {
        Position.X, Position.Y + offsetY, 0.0f,
        Position.X + offsetX, Position.Y + offsetY, 0.0f,
        Position.X, Position.Y, 0.0f,
        Position.X + offsetX, Position.Y, 0.0f};
}

void Rectangle::CopyUpdatedData()
{
    m_Vao.Bind();
    m_Vbo.Bind();
    m_Vbo.CopyData(m_Data.begin(), m_Data.size());
}