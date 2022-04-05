#include "Tetromino.hpp"
#include <cstring>

Tetromino::Tetromino(TetrisMath::IntPosition initialPosition, TetrisMath::Color shapeColor)
{
    m_Position = initialPosition;
    m_Color = shapeColor;
    memset(m_ShapeMap, 0, sizeof(m_ShapeMap));
}

void Tetromino::SetShape(EnumTetroShapes shape, bool shapeMap[4][4])
{
    m_Shape = shape;
    memcpy(m_ShapeMap, shapeMap, sizeof(m_ShapeMap));
    SetNearIndices();
}

void Tetromino::SetNearIndices()
{
    memset(m_RightIndices.Available, 0, sizeof(m_RightIndices.Available));
    memset(m_LeftIndices.Available, 0, sizeof(m_LeftIndices.Available));
    memset(m_DownIndices.Available, 0, sizeof(m_DownIndices.Available));
    for (uint8_t row = 0; row < 4; row++)
    {
        for (uint8_t column = 0; column <4; column++)
        {
            if (m_ShapeMap[row][column])
            {
                m_RightIndices.X[row] = m_Position.X + column + 1;
                m_RightIndices.Y[row] = m_Position.Y + row;
                m_RightIndices.Available[row] = true;
                if (!m_LeftIndices.Available[row])
                {
                    m_LeftIndices.X[row] = m_Position.X + column - 1;
                    m_LeftIndices.Y[row] = m_Position.Y + row;
                    m_LeftIndices.Available[row] = true;
                }
                m_DownIndices.Y[column] = m_Position.Y + row + 1;
                m_DownIndices.X[column] = m_Position.X + column;
                m_DownIndices.Available[column] = true;
            }
        }
    }
}

NearIndices Tetromino::GetRightIndices() const
{
    return m_RightIndices;
}

NearIndices Tetromino::GetLeftIndices() const
{
    return m_LeftIndices;
}
NearIndices Tetromino::GetDownIndices() const
{
    return m_DownIndices;
}

void Tetromino::UpdateLocation(int8_t xOffset, int8_t yOffset)
{
    m_Position.X += xOffset;
    m_Position.Y += yOffset;
    SetNearIndices();
}

RotationIndices Tetromino::GetRotatedIndices()
{
    RotationIndices result;
    // TODO: Implement Here!
    return result;
}

void Tetromino::GetShapeMap(bool shapeMap[4][4]) const
{
    for (uint8_t i = 0; i < 4; i++)
    {
        for (uint8_t j = 0; j < 4; j++)
        {
            shapeMap[i][j] = m_ShapeMap[i][j];
        }
    }
}
