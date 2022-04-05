#include "TetrominoGenerator.hpp"
#include <random>
using namespace TetrisMath;
TetrominoGenerator::TetrominoGenerator()
{
    IntPosition position;
    position.X = 5;
    position.Y = 0;
    srand(time(NULL));

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

Tetromino *TetrominoGenerator::GenerateTetromino()
{
    TetrisMath::Color color;
    color.R = static_cast<float>(static_cast<float>((rand() % 70) + 30) / 100);
    color.G = static_cast<float>(static_cast<float>((rand() % 70) + 30) / 100);
    color.B = static_cast<float>(static_cast<float>((rand() % 70) + 30) / 100);
    TetrisMath::IntPosition pos;
    pos.X = 8;
    Tetromino *tetro = new Tetromino(pos, color);
    bool shapeMap[4][4] = { 0 };
    m_Tetrominos[EnumTetroShapes::Z_SHAPE]->GetShapeMap(shapeMap);
    tetro->SetShape(EnumTetroShapes::Z_SHAPE, shapeMap);
    return tetro;
}