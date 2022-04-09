#ifndef _ENGINE_HPP_
#define _ENGINE_HPP_
#include "Map/TetrisMap.hpp"
#include "Tetromino/TetrominoGenerator.hpp"
#include <functional>
class Engine
{
public:
    Engine();
    void RightKeyPressed();
    void LeftKeyPressed();
    void DownKeyPressed();
    void UpKeyPressed();
    void TimeTick();
    Tetromino *GetFirstTetro();
    Tetromino *GetFirstNextTetro();
    void SetTetroChangedCallBack(std::function<void(Tetromino *, Tetromino *)> callback);
    TetrisMap *GetMap() ;
    void RunApplication();

private:
    std::function <void(Tetromino*, Tetromino*)> TetroChangedCallback;
    TetrisMap m_Map;
    TetrominoGenerator m_Generator;
    Tetromino *m_CurrentTetromino;
    Tetromino *m_NextTetromino;
    int64_t m_LeftKeyTimer;
    int64_t m_RightKeyTimer;
    int64_t m_DownKeyTimer;
    int64_t m_UpKeyTimer;
    int64_t m_GravityTimer;
    static constexpr int32_t KEY_TIME = 50;
    static constexpr int32_t UP_KEY_TIME = 200;
    static constexpr int32_t TICK_TIME = 750;
    int64_t GetTimeInMilliSecond() const;
    void PassTetroToMapAndSetCurrentToNew();
};
#endif