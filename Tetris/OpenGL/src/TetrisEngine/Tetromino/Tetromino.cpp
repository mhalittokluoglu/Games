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

void Tetromino::RotateShape(bool rotatedShape[4][4])
{
    for (int8_t i = 0; i < 4; i++)
    {
        for (int8_t j = 0; j < 4; j++)
        {
            m_ShapeMap[i][j] = rotatedShape[i][j];
        }
    }
    SetNearIndices();
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

ShapeMap Tetromino::GetRotatedShapeMap()
{
    ShapeMap rotated;
    rotated.map[0][0] = m_ShapeMap[0][3];
    rotated.map[0][1] = m_ShapeMap[1][3];
    rotated.map[0][2] = m_ShapeMap[2][3];
    rotated.map[0][3] = m_ShapeMap[3][3];
    rotated.map[1][0] = m_ShapeMap[0][2];
    rotated.map[1][1] = m_ShapeMap[1][2];
    rotated.map[1][2] = m_ShapeMap[2][2];
    rotated.map[1][3] = m_ShapeMap[3][2];
    rotated.map[2][0] = m_ShapeMap[0][1];
    rotated.map[2][1] = m_ShapeMap[1][1];
    rotated.map[2][2] = m_ShapeMap[2][1];
    rotated.map[2][3] = m_ShapeMap[3][1];
    rotated.map[3][0] = m_ShapeMap[0][0];
    rotated.map[3][1] = m_ShapeMap[1][0];
    rotated.map[3][2] = m_ShapeMap[2][0];
    rotated.map[3][3] = m_ShapeMap[3][0];
    return rotated;
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
