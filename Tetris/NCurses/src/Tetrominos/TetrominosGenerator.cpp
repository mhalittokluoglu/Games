#include "TetrominosGenerator.hpp"
#include <cstdlib>
#include <time.h>

TetrominosGenerator::TetrominosGenerator()
{
    srand(time(NULL));
    GenerateAllTetrominos();
}

Tetrominos *TetrominosGenerator::GetTetrominos()
{
    EnumShape shape = static_cast<EnumShape> (rand() % NUMBER_OF_SHAPES);
    EnumColor color = static_cast<EnumColor> ((rand() % 7) + 1);
    EnumColor prevColor = RED;
    if (color == prevColor)
    {
        color = static_cast<EnumColor>((color + 2)%7 + 1);
    }
    prevColor = color;

    Tetrominos *generatedTetrominos = new Tetrominos;
    generatedTetrominos->Copy(m_Tetrominouses[shape]);
    generatedTetrominos->color = color;
    generatedTetrominos->shape = shape;

    // generatedTetrominos->Copy(m_Tetrominouses[I_SHAPE]);
    // generatedTetrominos->color = color;
    return generatedTetrominos;
}

void TetrominosGenerator::GenerateAllTetrominos()
{
    m_Tetrominouses = new Tetrominos[NUMBER_OF_SHAPES];

    m_Tetrominouses[T_SHAPE].size = 9;
    m_Tetrominouses[T_SHAPE].block = new bool[9]
        {0, 1, 0,
         1, 1, 1,
         0, 0, 0};
    m_Tetrominouses[T_SHAPE].xSize = 3;
    m_Tetrominouses[T_SHAPE].ySize = 3;

    m_Tetrominouses[I_SHAPE].size = 16;
    m_Tetrominouses[I_SHAPE].block = new bool[16]
        {0, 1, 0, 0,
         0, 1, 0, 0,
         0, 1, 0, 0,
         0, 1, 0, 0};
    m_Tetrominouses[I_SHAPE].xSize = 4;
    m_Tetrominouses[I_SHAPE].ySize = 4;

    m_Tetrominouses[L_SHAPE].size = 9;
    m_Tetrominouses[L_SHAPE].block = new bool[9]
        {0, 1, 0,
         0, 1, 0,
         0, 1, 1};
    m_Tetrominouses[L_SHAPE].xSize = 3;
    m_Tetrominouses[L_SHAPE].ySize = 3;

    m_Tetrominouses[REVERSE_L_SHAPE].size = 9;
    m_Tetrominouses[REVERSE_L_SHAPE].block = new bool[9]
        {0, 1, 0,
         0, 1, 0,
         1, 1, 0};
    m_Tetrominouses[REVERSE_L_SHAPE].xSize = 3;
    m_Tetrominouses[REVERSE_L_SHAPE].ySize = 3;
    
    m_Tetrominouses[Z_SHAPE].size = 9;
    m_Tetrominouses[Z_SHAPE].block = new bool[9]
        {0, 0, 0,
         1, 1, 0,
         0, 1, 1};
    m_Tetrominouses[Z_SHAPE].xSize = 3;
    m_Tetrominouses[Z_SHAPE].ySize = 3;

    m_Tetrominouses[REVERSE_Z_SHAPE].size = 9;
    m_Tetrominouses[REVERSE_Z_SHAPE].block = new bool[9]
        {0, 0, 0,
         0, 1, 1,
         1, 1, 0};
    m_Tetrominouses[REVERSE_Z_SHAPE].xSize = 3;
    m_Tetrominouses[REVERSE_Z_SHAPE].ySize = 3;

    m_Tetrominouses[CUBE_SHAPE].size = 4;
    m_Tetrominouses[CUBE_SHAPE].block = new bool[4]
        {1, 1,
         1, 1};
    m_Tetrominouses[CUBE_SHAPE].xSize = 2;
    m_Tetrominouses[CUBE_SHAPE].ySize = 2;

    for (uint8_t i = 0; i < NUMBER_OF_SHAPES; i++)
    {
        m_Tetrominouses[i].xPos = 15;
        m_Tetrominouses[i].yPos = 1;
    }
}