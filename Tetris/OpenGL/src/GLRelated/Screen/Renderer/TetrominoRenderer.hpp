#ifndef _TETROMINORENDERER_HPP_
#define _TETROMINORENDERER_HPP_
#include "Rectangle.hpp"
#include "GLRelated/Vertex/VertexArray.hpp"
#include "GLRelated/Vertex/ElementBuffer.hpp"


class TetrominoRenderer
{
public:
    TetrominoRenderer();
    void Initialize(ShaderProgram *shaderProgram);
    void SetTetromino(bool tetroMap[][4], 
    TetrisMath::IntPosition position, TetrisMath::Color color);
    void DrawTetromino();
    void DeleteTetromino();
private:
    std::array<Rectangle,16> m_Rectangles;
    uint8_t m_RectangleCount;

};

#endif