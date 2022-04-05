#include "TetrisMap.hpp"

TetrisMapSquare::TetrisMapSquare()
{
    exist = false;
}

int32_t TetrisMap::s_RowCount;
int32_t TetrisMap::s_ColumnCount;
bool TetrisMap::s_Initalized = false;

TetrisMap::TetrisMap()
{
    if (!s_Initalized)
    {
        Initialize();
        s_Initalized = true;
    }
    m_Map = new TetrisMapSquare*[s_RowCount]; 
    for (int32_t i = 0; i < s_RowCount; i++)
    {
        TetrisMapSquare *rowMap = new TetrisMapSquare[s_ColumnCount];
        m_Map[i] = rowMap; 
    }
}
void TetrisMap::Initialize()
{
    s_RowCount = TetrisMath::Globals::s_RowCount;
    s_ColumnCount = TetrisMath::Globals::s_ColumnCount;
}

void TetrisMap::SetMapCell(int32_t row, int32_t column, TetrisMath::Color color)
{
    m_Map[row][column].color = color;
    m_Map[row][column].exist = true;
}

void TetrisMap::ClearMapCell(int32_t row, int32_t column)
{
    m_Map[row][column].exist = false;
}

bool TetrisMap::GetMapCell(int32_t row, int32_t column) const
{
    if (column < s_ColumnCount - 1&& row < s_RowCount &&
        column >= 0 && row >= 0)
    {
        return !m_Map[row][column].exist;
    }
    return false;
}