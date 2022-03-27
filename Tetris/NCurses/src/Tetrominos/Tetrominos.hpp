#ifndef _TETROMINOS_HPP_
#define _TETROMINOS_HPP_
#include <inttypes.h>
#define NUMBER_OF_SHAPES 7

enum EnumShape
{
    T_SHAPE = 0,
    I_SHAPE = 1,
    L_SHAPE = 2,
    REVERSE_L_SHAPE = 3,
    Z_SHAPE = 4,
    REVERSE_Z_SHAPE = 5,
    CUBE_SHAPE = 6

};

enum EnumColor
{
    BLACK   = 0,
    RED     = 1,
    GREEN   = 2,
    YELLOW  = 3,
    BLUE    = 4,
    MAGENTA = 5,
    CYAN    = 6,
    WHITE   = 7
};

struct Tetrominos
{
    bool *block;
    int16_t xPos;
    int16_t yPos;
    EnumColor color;
    uint8_t size;
    uint8_t xSize;
    uint8_t ySize;
    EnumShape shape;
    void Copy(const Tetrominos &other);
    Tetrominos();
    ~Tetrominos();
};
#endif