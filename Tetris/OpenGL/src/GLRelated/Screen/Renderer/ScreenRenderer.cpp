#include "ScreenRenderer.hpp"

ScreenRenderer::ScreenRenderer()
{
}

void ScreenRenderer::Initialize(ShaderProgram *shaderProgram, TetrisMap *map)
{
    m_Borders[0].Initialize(shaderProgram);
    m_Borders[1].Initialize(shaderProgram);
    m_Borders[2].Initialize(shaderProgram);
    SetBorders();
    m_TetrisMap = map;

    m_Rectangles = new TetrisShapes::Rectangle* [TetrisMap::s_RowCount];
    for (int32_t row = 0; row < TetrisMap::s_RowCount; row++)
    {
        TetrisShapes::Rectangle *rowRectangle = new TetrisShapes::Rectangle[m_TetrisMap->s_ColumnCount];
        for (int32_t column = 0; column < TetrisMap::s_ColumnCount; column++)
        {
            rowRectangle[column].Initialize(shaderProgram);
        }
        m_Rectangles[row] = rowRectangle;
    }
}

void ScreenRenderer::SetBorders()
{
    using namespace TetrisMath;
    Color borderColor;
    borderColor.R = 0.3f;
    borderColor.G = 0.2f;
    borderColor.B = 0.4f;

    m_Borders[0].Position.X = -1.0f; m_Borders[0].Position.Y = 1.0f;
    m_Borders[0].SetBorderData(Globals::BorderSizeX, -2.0f);
    m_Borders[0].CopyUpdatedData();
    m_Borders[0].Color = borderColor;

    m_Borders[1].Position.X = -1.0f + Globals::GameWidth - Globals::BorderSizeX; m_Borders[1].Position.Y = 1.0f;
    m_Borders[1].SetBorderData(Globals::BorderSizeX, -2.0f);
    m_Borders[1].CopyUpdatedData();
    m_Borders[1].Color = borderColor;

    m_Borders[2].Position.X = -1.0f; m_Borders[2].Position.Y = -1.0f;
    m_Borders[2].SetBorderData(Globals::GameWidth, Globals::BorderSizeY);
    m_Borders[2].CopyUpdatedData();
    m_Borders[2].Color = borderColor;
}


void ScreenRenderer::DrawScreen()
{
    m_Borders[0].Draw();
    m_Borders[1].Draw();
    m_Borders[2].Draw();
    
    for(int32_t row = 0; row < TetrisMap::s_RowCount; row++)
    {
        for (int32_t column = 0; column < TetrisMap::s_ColumnCount; column++)
        {
            if (m_TetrisMap->Map()[row][column].exist)
            {
                m_Rectangles[row][column].Color = m_TetrisMap->Map()[row][column].color;
                TetrisMath::IntPosition position;
                position.Y = row;
                position.X = column;
                m_Rectangles[row][column].Position = position.ConvertToGLPosition();
                m_Rectangles[row][column].UpdateData();
                m_Rectangles[row][column].CopyUpdatedData();
                m_Rectangles[row][column].Draw();
            }
        }
    }
}