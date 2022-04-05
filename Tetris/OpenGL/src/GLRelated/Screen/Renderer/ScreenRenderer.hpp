#ifndef _SCREENRENDERER_HPP_
#define _SCREENRENDERER_HPP_
#include "Rectangle.hpp"
#include "TetrisEngine/Map/TetrisMap.hpp"
class ScreenRenderer
{
public:
    ScreenRenderer();
    void Initialize(ShaderProgram *shaderProgram, TetrisMap *map);
    void DrawScreen();
private:
    void SetBorders();
    std::array<TetrisShapes::Rectangle,3> m_Borders;
    TetrisMap *m_TetrisMap;
    TetrisShapes::Rectangle **m_Rectangles;
};
#endif