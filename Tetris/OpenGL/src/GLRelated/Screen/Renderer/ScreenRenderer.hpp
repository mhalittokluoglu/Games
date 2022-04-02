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
    static constexpr uint8_t BORDERSIZE = 3; 
    Rectangle m_Borders[BORDERSIZE];
};
#endif