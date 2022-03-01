#ifndef _TETROMINOS_HPP_
#define _TETROMINOS_HPP_
#include <inttypes.h>

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
    void Copy(const Tetrominos &other);
    Tetrominos();
    ~Tetrominos();
};
#endif