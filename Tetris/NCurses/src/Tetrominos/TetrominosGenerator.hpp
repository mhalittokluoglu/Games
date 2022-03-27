#ifndef _TETROMINOSGENERATOR_HPP_
#define _TETROMINOSGENERATOR_HPP_
#include "Tetrominos.hpp"


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