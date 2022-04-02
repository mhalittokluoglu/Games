#ifndef _SCREENRENDERER_HPP_
#define _SCREENRENDERER_HPP_
#include "Rectangle.hpp"
#include <array>
class ScreenRenderer
{
public:
    ScreenRenderer();
    void Initialize(ShaderProgram *shaderProgram);
    void DrawScreen();
private:
    void SetBorders();
    std::array<Rectangle,3> m_Borders;
};
#endif