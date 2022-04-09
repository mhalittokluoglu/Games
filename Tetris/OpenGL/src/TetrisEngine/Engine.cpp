#include "Engine.hpp"
#include <chrono>

Engine::Engine()
{
    m_CurrentTetromino = m_Generator.GenerateTetromino();
    m_NextTetromino = m_Generator.GenerateTetromino();
    int64_t currentTime = GetTimeInMilliSecond();
    m_LeftKeyTimer = currentTime;
    m_RightKeyTimer = currentTime;
    m_DownKeyTimer = currentTime;
    m_UpKeyTimer = currentTime;
    m_GravityTimer = currentTime;
}

void Engine::SetTetroChangedCallBack(std::function<void(Tetromino *, Tetromino *)> callback)
{
    TetroChangedCallback = callback;
}

TetrisMap *Engine::GetMap()
{
    return &m_Map;
}

Tetromino *Engine::GetFirstTetro()
{
    return m_CurrentTetromino;
}

Tetromino *Engine::GetFirstNextTetro()
{
    return m_NextTetromino;
}

void Engine::RunApplication()
{
    TimeTick();
}

void Engine::UpKeyPressed()
{
    int64_t currentTime = GetTimeInMilliSecond();
    int64_t offset = currentTime - m_UpKeyTimer;
    if (offset > UP_KEY_TIME)
    {
        ShapeMap rotated;
        rotated = m_CurrentTetromino->GetRotatedShapeMap();
        TetrisMath::IntPosition currentTetroPosition = m_CurrentTetromino->GetPosition();
        bool validToRotate = true;
        for (int8_t i = 0; i < 4; i++)
        {
            for (int8_t j = 0; j < 4; j++)
            {
                if (rotated.map[i][j])
                {
                    int8_t column = currentTetroPosition.X + j;
                    int8_t row = currentTetroPosition.Y + i;
                    if (row < TetrisMath::Globals::s_RowCount&&
                        column < (TetrisMath::Globals::s_ColumnCount - 1) &&
                        row > 0 &&
                        column > -1)
                    {
                        if (m_Map.Map()[row][column].exist)
                        {
                            validToRotate = false;
                        }
                    }
                    else
                    {
                        validToRotate = false;
                    }
                }
            }
        }
        if (validToRotate)
        {
            m_CurrentTetromino->RotateShape(rotated.map);
            m_UpKeyTimer = currentTime;
        }
    }
}

void Engine::RightKeyPressed()
{
    int64_t currentTime = GetTimeInMilliSecond();
    int64_t offset = currentTime - m_RightKeyTimer;
    if (offset > KEY_TIME)
    {
        NearIndices indices;
        indices = m_CurrentTetromino->GetRightIndices();
        bool valid = true;
        for (int8_t i = 0; i < 5; i++)
        {
            if (indices.Available[i])
            {
                if (valid)
                {
                    int32_t row = indices.Y[i];
                    int32_t column = indices.X[i];
                    valid = m_Map.GetMapCell(row, column);
                }
            }
        }
        if (valid)
        {
            m_CurrentTetromino->UpdateLocation(1, 0);
            m_RightKeyTimer = currentTime;
        }
    }
}

void Engine::LeftKeyPressed()
{
    int64_t currentTime = GetTimeInMilliSecond();
    int64_t offset = currentTime - m_LeftKeyTimer;
    if (offset > KEY_TIME)
    {
        NearIndices indices;
        indices = m_CurrentTetromino->GetLeftIndices();
        bool valid = true;
        for (int8_t i = 0; i < 5; i++)
        {
            if (indices.Available[i])
            {
                if (valid)
                {
                    int32_t row = indices.Y[i];
                    int32_t column = indices.X[i];
                    valid = m_Map.GetMapCell(row, column);
                }
            }
        }
        if (valid)
        {
            m_CurrentTetromino->UpdateLocation(-1, 0);
            m_LeftKeyTimer = currentTime;
        }
    }
}

void Engine::DownKeyPressed()
{
    int64_t currentTime = GetTimeInMilliSecond();
    int64_t offset = currentTime - m_DownKeyTimer;
    if (offset > KEY_TIME)
    {
        NearIndices indices;
        indices = m_CurrentTetromino->GetDownIndices();
        bool valid = true;
        for (int8_t i = 0; i < 5; i++)
        {
            if (indices.Available[i])
            {
                if (valid)
                {
                    int32_t row = indices.Y[i];
                    int32_t column = indices.X[i];
                    valid = m_Map.GetMapCell(row, column);
                }
            }
        }
        if (valid)
        {
            m_CurrentTetromino->UpdateLocation(0, 1);
            m_DownKeyTimer = currentTime;
        }
        else
        {
            PassTetroToMapAndSetCurrentToNew();
        }
    }
}

void Engine::TimeTick()
{
    int64_t currentTime = GetTimeInMilliSecond();
    int64_t offset = currentTime - m_GravityTimer;
    if (offset > TICK_TIME)
    {
        NearIndices indices;
        indices = m_CurrentTetromino->GetDownIndices();
        bool valid = true;
        for (int8_t i = 0; i < 5; i++)
        {
            if (indices.Available[i])
            {
                if (valid)
                {
                    int32_t row = indices.Y[i];
                    int32_t column = indices.X[i];
                    valid = m_Map.GetMapCell(row, column);
                }
            }
        }
        if (valid)
        {
            m_CurrentTetromino->UpdateLocation(0, 1);
            m_GravityTimer = currentTime;
        }
        else
        {
            PassTetroToMapAndSetCurrentToNew();
        }
    }
}

int64_t Engine::GetTimeInMilliSecond() const
{
    using std::chrono::duration_cast;
    using std::chrono::milliseconds;
    using std::chrono::seconds;
    using std::chrono::system_clock;
    auto millisec_since_epoch = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    return millisec_since_epoch;
}

void Engine::PassTetroToMapAndSetCurrentToNew()
{
    TetrisMath::IntPosition position;
    position = m_CurrentTetromino->GetPosition();
    bool shapeMap[4][4] = {0};
    m_CurrentTetromino->GetShapeMap(shapeMap);
    for (int8_t i = 0; i < 4; i++)
    {
        for (int8_t j = 0; j < 4; j++)
        {
            if (shapeMap[i][j])
            {
                m_Map.SetMapCell(position.Y + i, position.X + j, m_CurrentTetromino->GetColor());
            }
        }
    }
    delete m_CurrentTetromino;
    m_CurrentTetromino = m_NextTetromino;
    TetrisMath::IntPosition pos;
    pos.X = 8;
    m_CurrentTetromino->SetPosition(pos);
    m_NextTetromino = m_Generator.GenerateTetromino();
    TetroChangedCallback(m_CurrentTetromino, m_NextTetromino);
    m_Map.ClearFullRows();
}