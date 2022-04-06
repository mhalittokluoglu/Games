#include "TetrominoGenerator.hpp"
#include <random>
#include <time.h>

using namespace TetrisMath;
TetrominoGenerator::TetrominoGenerator()
{
    IntPosition position;
    position.X = 5;
    position.Y = 0;
    srand(time(NULL));

    Color color;
    color.R = 2.0f;

    bool inverseLShapeMap[4][4] = {
        0, 0, 1, 0,
        0, 0, 1, 0,
        0, 1, 1, 0,
        0, 0, 0, 0,
    };
    m_Tetrominos[EnumTetroShapes::INVERSE_L_SHAPE] = new Tetromino(position, color);
    m_Tetrominos[EnumTetroShapes::INVERSE_L_SHAPE]->SetShape(EnumTetroShapes::INVERSE_L_SHAPE, inverseLShapeMap);

     bool InverseZShape[4][4] = {
        0, 0, 0, 0,
        0, 0, 1, 1,
        0, 1, 1, 0,
        0, 0, 0, 0,
    };

    m_Tetrominos[EnumTetroShapes::INVERSE_Z_SHAPE] = new Tetromino(position, color);
    m_Tetrominos[EnumTetroShapes::INVERSE_Z_SHAPE]->SetShape(EnumTetroShapes::INVERSE_Z_SHAPE, InverseZShape);

    bool lShape[4][4] = {
        0, 1, 0, 0,
        0, 1, 0, 0,
        0, 1, 1, 0,
        0, 0, 0, 0,
    };

    m_Tetrominos[EnumTetroShapes::L_SHAPE] = new Tetromino(position, color);
    m_Tetrominos[EnumTetroShapes::L_SHAPE]->SetShape(EnumTetroShapes::L_SHAPE, lShape);

    bool squareShape[4][4] = {
        0, 0, 0, 0,
        0, 1, 1, 0,
        0, 1, 1, 0,
        0, 0, 0, 0,
    };
    m_Tetrominos[EnumTetroShapes::SQUARE_SHAPE] = new Tetromino(position, color);
    m_Tetrominos[EnumTetroShapes::SQUARE_SHAPE]->SetShape(EnumTetroShapes::SQUARE_SHAPE, squareShape);

    bool stickShape[4][4] = {
        0, 1, 0, 0,
        0, 1, 0, 0,
        0, 1, 0, 0,
        0, 1, 0, 0,
    };
    m_Tetrominos[EnumTetroShapes::STICK_SHAPE] = new Tetromino(position, color);
    m_Tetrominos[EnumTetroShapes::STICK_SHAPE]->SetShape(EnumTetroShapes::STICK_SHAPE, stickShape);

    bool tShape[4][4] = {
        0, 0, 0, 0,
        0, 1, 0, 0,
        1, 1, 1, 0,
        0, 0, 0, 0,
    };
    m_Tetrominos[EnumTetroShapes::T_SHAPE] = new Tetromino(position, color);
    m_Tetrominos[EnumTetroShapes::T_SHAPE]->SetShape(EnumTetroShapes::T_SHAPE, tShape);

    bool zShapeMap[4][4] = {
        0, 0, 0, 0,
        1, 1, 0, 0,
        0, 1, 1, 0,
        0, 0, 0, 0,
    };
    m_Tetrominos[EnumTetroShapes::Z_SHAPE] = new Tetromino(position, color);
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

    EnumTetroShapes shape = static_cast<EnumTetroShapes>((rand() % 7) + 1);

    m_Tetrominos[shape]->GetShapeMap(shapeMap);
    tetro->SetShape(shape, shapeMap);
    return tetro;
}