#include "TetrominoRenderer.hpp"
#include "Logger/Logger.hpp"

TetrominoRenderer::TetrominoRenderer()
{

}

void TetrominoRenderer::SetTetromino(bool tetroMap[][4],
    TetrisMath::IntPosition position, TetrisMath::Color color)
{
    m_RectangleCount = 0;
    for (uint8_t i = 0; i < 4; i++)
    {
        for (uint8_t j = 0; j < 4; j++)
        {
            if (tetroMap[i][j])
            {
                TetrisMath::IntPosition rectIntPos;
                rectIntPos.X = position.X + j;
                rectIntPos.Y = position.X + i;
                TetrisMath::GLPosition rectPos;
                m_Rectangles[m_RectangleCount].Position = rectIntPos.ConvertToGLPosition();
                m_Rectangles[m_RectangleCount].Color = color;
                m_Rectangles[m_RectangleCount].UpdateData();
                m_Rectangles[m_RectangleCount].CopyUpdatedData();
                Logger::LOG_DEBUG("TetrominoRenderer:: Registered Rectangle count: %d", m_RectangleCount);
                m_RectangleCount++;
            }
        }
    }
}

void TetrominoRenderer::Initialize(ShaderProgram *shaderProgram)
{
    Logger::LOG_DEBUG("TetrominoRenderer::Initialized shaderProgram passed To Rectangles");
    for(uint8_t i = 0; i < RECTANGLESIZE; i++)
    {
        m_Rectangles[i].Initialize(shaderProgram);
    }
}

void TetrominoRenderer::DeleteTetromino()
{
}

void TetrominoRenderer::DrawTetromino()
{
    for (uint8_t i = 0; i < m_RectangleCount; i++)
    {
        m_Rectangles[i].Draw();
    }
}
