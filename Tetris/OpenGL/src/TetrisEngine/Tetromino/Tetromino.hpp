#ifndef _SHAPES_TETROMINOZ_HPP_
#define _SHAPES_TETROMINOZ_HPP_
#include "ITetromino.hpp"
#include "TetrisEngine/MathLib/TetrisMath.hpp"

class Tetromino : public ITetromino
{
public:
    Tetromino(TetrisMath::IntPosition initialPosition, TetrisMath::Color shapeColor);
    void SetShape(EnumTetroShapes shape, bool shapeMap[4][4]);
    void UpdateLocation(int8_t xOffset, int8_t yOffset);
    NearIndices GetRightIndices() const override;
    NearIndices GetLeftIndices() const override;
    NearIndices GetDownIndices() const override;
    RotationIndices GetRotatedIndices() override;
    inline EnumTetroShapes GetTetroShape() const { return m_Shape;};

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
