#include "Rectangle.hpp"
#include <cstring>

using namespace Shapes;

Rectangle::Rectangle(ShapePosition position, ShapeSize size, Vect3 color)
            : m_Position { position }, m_Size { size }, m_Color { color },
            m_IsMoving {true}
{
    memset(m_Data, 0, sizeof(m_Data));

    float data[] = {
        m_Position.X,                   m_Position.Y + m_Size.Height,   0,
        m_Position.X + m_Size.Width,    m_Position.Y + m_Size.Height,   0,
        m_Position.X,                   m_Position.Y,                   0,
        m_Position.X + m_Size.Width,    m_Position.Y,                   0
    };
    memcpy(m_Data, data, sizeof(m_Data));

    uint32_t indices[] = {
    0, 1, 2,
    1, 3, 2
    };
    
    memcpy(m_Indices, indices, sizeof(m_Indices));
}
void Rectangle::SetBuffers()
{
    m_VertexArray.Bind();
    m_ElementBuffer.Bind();
    m_ElementBuffer.CopyData(m_Indices, sizeof(m_Indices));
    m_VertexBuffer.Bind();
    m_VertexBuffer.CopyData(m_Data, sizeof(m_Data));
    m_VertexBuffer.AddLayout(0);
    m_VertexBuffer.Unbind();
    m_VertexArray.Unbind();
    m_ElementBuffer.Unbind();
}


Rectangle::~Rectangle()
{
}

void Rectangle::Draw()
{
    m_VertexArray.Bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    m_VertexArray.Unbind();
}

Vect3 Rectangle::Color()
{
    return m_Color;
}

bool Rectangle::IsMoving()
{
    return m_IsMoving;
}

void Rectangle::UpdateLocation()
{
    if (m_Position.Y > -1.0f)
    {
        m_Position.Y    -= 0.01;
        m_Data[1]       =  m_Position.Y + m_Size.Height;
        m_Data[4]       =  m_Position.Y + m_Size.Height;
        m_Data[7]       =  m_Position.Y;
        m_Data[10]      =  m_Position.Y;
    }
    else
    {
        m_IsMoving = false;
    }
    SetBuffers();
}
