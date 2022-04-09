#include "TetrisMap.hpp"
#include <vector>

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
    if (column < s_ColumnCount - 1 && row < s_RowCount &&
        column >= 0 && row >= 0)
    {
        return !m_Map[row][column].exist;
    }
    return false;
}

void TetrisMap::ClearFullRows() const
{
    bool bFullRowExist = false;
    std::vector<int16_t> notFullRowList;
    for (int16_t row = s_RowCount - 1; row >= 0; row--)
    {
        bool IsFullRow = true;
        for(int16_t column = 0; column < s_ColumnCount - 1; column++)
        {
            if (!m_Map[row][column].exist)
            {
                IsFullRow = false;
            }
        }
        if (!IsFullRow)
        {
            notFullRowList.push_back(row);
        }
        else
        {
            bFullRowExist = true;
        }
    }

    if (!bFullRowExist)
        return;

    TetrisMapSquare **tempMap = new TetrisMapSquare*[s_RowCount]; 
    for (int32_t i = 0; i < s_RowCount; i++)
    {
        TetrisMapSquare *rowMap = new TetrisMapSquare[s_ColumnCount];
        tempMap[i] = rowMap; 
    }
    for (int16_t i = 0; i < s_RowCount; i++)
    {
        for (int16_t j = 0; j < s_ColumnCount; j++)
        {
            tempMap[i][j].exist = m_Map[i][j].exist;
            tempMap[i][j].color = m_Map[i][j].color;
        }
    }

    for (int16_t i = 0; i < notFullRowList.size();i++)
    {
        for (int16_t j = 0; j < s_ColumnCount - 1; j++)
        {
            m_Map[s_RowCount - 1 - i][j].exist = tempMap[notFullRowList[i]][j].exist;
            m_Map[s_RowCount - 1 - i][j].color = tempMap[notFullRowList[i]][j].color;
        }
    }
}