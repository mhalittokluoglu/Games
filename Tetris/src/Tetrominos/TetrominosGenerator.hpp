#ifndef _TETROMINOSGENERATOR_HPP_
#define _TETROMINOSGENERATOR_HPP_
#include "Tetrominos.hpp"
#define NUMBER_OF_SHAPES 5
enum EnumShape
{
    T_SHAPE = 0,
    I_SHAPE = 1,
    L_SHAPE = 2,
    Z_SHAPE = 3,
    CUBE_SHAPE = 4

};

class TetrominosGenerator
{
public:
    TetrominosGenerator();
    Tetrominos *GetTetrominos();

private:
    void GenerateAllTetrominos();
    Tetrominos *m_Tetrominouses;
};
#endif