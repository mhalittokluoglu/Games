#ifndef _SHAPES_TETROMINO_HPP_
#define _SHAPES_TETROMINO_HPP_
#include "TetrisEngine/MathLib/TetrisMath.hpp"
#include "TetrominoData.hpp"

class ITetromino
{
public:
    virtual NearIndices GetRightIndices() const = 0;
    virtual NearIndices GetLeftIndices() const = 0;
    virtual NearIndices GetDownIndices() const = 0;
    virtual RotationIndices GetRotatedIndices() = 0;
};

#endif