#ifndef _SCREENRENDERER_HPP_
#define _SCREENRENDERER_HPP_
#include "Rectangle.hpp"
class ScreenRenderer
{
public:
    ScreenRenderer();
    void Initialize(ShaderProgram *shaderProgram);
    void DrawScreen();
private:
    void SetBorders();
    std::array<TetrisShapes::Rectangle,3> m_Borders;
};
#endif