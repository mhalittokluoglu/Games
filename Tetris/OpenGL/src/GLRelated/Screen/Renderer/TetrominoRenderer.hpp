#ifndef _TETROMINORENDERER_HPP_
#define _TETROMINORENDERER_HPP_
#include "Rectangle.hpp"
#include "GLRelated/Vertex/VertexArray.hpp"
#include "GLRelated/Vertex/ElementBuffer.hpp"
#include <array>


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
    static constexpr uint8_t RECTANGLESIZE = 16;
    Rectangle m_Rectangles[RECTANGLESIZE];
    uint8_t m_RectangleCount;

};

#endif