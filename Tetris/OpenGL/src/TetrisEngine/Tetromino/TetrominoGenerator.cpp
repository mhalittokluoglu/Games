#include "TetrominoGenerator.hpp"
#include <random>
using namespace TetrisMath;
TetrominoGenerator::TetrominoGenerator()
{
    IntPosition position;
    position.X = 5;
    position.Y = 0;

    Color color;
    color.R = 2.0f;
    m_Tetrominos[EnumTetroShapes::Z_SHAPE] = new Tetromino(position, color);
    bool zShapeMap[4][4] = {
        1, 1, 0, 0,
        0, 1, 1, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
    };
    m_Tetrominos[EnumTetroShapes::Z_SHAPE]->SetShape(EnumTetroShapes::Z_SHAPE, zShapeMap);

}