#ifndef _TETROMINOGENERATOR_HPP_
#define _TETROMINOGENERATOR_HPP_
#include "Tetromino.hpp"
class TetrominoGenerator
{
public:
    TetrominoGenerator();
    Tetromino *GenerateTetromino();
private:
    Tetromino *m_Tetrominos[8];
};
#endif