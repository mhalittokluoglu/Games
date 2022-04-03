#ifndef _TETRISMAP_HPP_
#define _TETRISMAP_HPP_
#include "TetrisEngine/MathLib/TetrisMath.hpp"
struct TetrisMapSquare
{
    TetrisMapSquare();
    TetrisMath::Color color;
    bool exist;
};

class ScreenRenderer;
class TetrisMap
{
public:
    TetrisMap();
    void Initialize();
    void SetMapCell(int32_t row, int32_t column, TetrisMath::Color color);
    void ClearMapCell(int32_t row, int32_t column);
private:
    static int32_t s_RowCount;
    static int32_t s_ColumnCount;
    TetrisMapSquare **m_Map;
    static bool s_Initalized;

    friend class ScreenRenderer;
};
#endif