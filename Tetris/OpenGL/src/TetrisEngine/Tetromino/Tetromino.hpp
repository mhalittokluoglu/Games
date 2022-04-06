#ifndef _SHAPES_TETROMINOZ_HPP_
#define _SHAPES_TETROMINOZ_HPP_
#include "TetrominoData.hpp"
#include "TetrisEngine/MathLib/TetrisMath.hpp"

struct ShapeMap
{
    bool map[4][4];
};

class Tetromino
{
public:
    Tetromino(TetrisMath::IntPosition initialPosition, TetrisMath::Color shapeColor);
    void SetShape(EnumTetroShapes shape, bool shapeMap[4][4]);
    void UpdateLocation(int8_t xOffset, int8_t yOffset);
    NearIndices GetRightIndices() const;
    NearIndices GetLeftIndices() const;
    NearIndices GetDownIndices() const;
    inline EnumTetroShapes GetTetroShape() const { return m_Shape;};
    void GetShapeMap(bool shapeMap[4][4]) const;
    inline TetrisMath::IntPosition GetPosition() const { return m_Position; }
    inline TetrisMath::Color GetColor() const { return m_Color; }
    ShapeMap GetRotatedShapeMap();
    void RotateShape(bool rotatedShape[4][4]);

private:
    void SetNearIndices();
    bool m_ShapeMap[4][4];
    NearIndices m_RightIndices;
    NearIndices m_LeftIndices;
    NearIndices m_DownIndices;
    TetrisMath::Color m_Color;
    TetrisMath::IntPosition m_Position;
    EnumTetroShapes m_Shape;
};

#endif
