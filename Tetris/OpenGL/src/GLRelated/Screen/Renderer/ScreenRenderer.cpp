#include "ScreenRenderer.hpp"

ScreenRenderer::ScreenRenderer()
{
}

void ScreenRenderer::Initialize(ShaderProgram *shaderProgram)
{
    using namespace TetrisMath;
    m_Borders[0].Initialize(shaderProgram);
    m_Borders[1].Initialize(shaderProgram);
    m_Borders[2].Initialize(shaderProgram);
    SetBorders();
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
}