#include "Tetrominos.hpp"

Tetrominos::Tetrominos()
{
    block = nullptr;
    xPos = 0;
    yPos = 0;
    color = RED;
    size = 0;
    xSize = 0;
    ySize = 0;
}

Tetrominos::~Tetrominos()
{
    delete[] block;
}


void Tetrominos::Copy(const Tetrominos &other)
{
    this->size = other.size;
    this->block = new bool[this->size];
    for (uint8_t i = 0; i < this->size; i++)
    {
        this->block[i] = other.block[i];
    }
    this->color = other.color;
    this->xPos = other.xPos;
    this->yPos = other.yPos;
    this->xSize = other.xSize;
    this->ySize = other.ySize;
}
