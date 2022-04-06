#ifndef _TETROMINODATA_HPP_
#define _TETROMINODATA_HPP_
#include <inttypes.h>
#include "TetrisEngine/MathLib/TetrisMath.hpp"
enum EnumTetroShapes
{
    INVALID = 0,
    Z_SHAPE = 1,
    INVERSE_Z_SHAPE = 2,
    T_SHAPE = 3,
    STICK_SHAPE = 4,
    SQUARE_SHAPE = 5,
    L_SHAPE = 6,
    INVERSE_L_SHAPE = 7
};

struct NearIndices
{
    int32_t X[5];
    int32_t Y[5];
    bool Available[5];
    NearIndices();
};

#endif