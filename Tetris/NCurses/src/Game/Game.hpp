#ifndef _GAME_HPP_
#define _GAME_HPP_
#include <ncurses.h>
#include "../Tetrominos/TetrominosGenerator.hpp"
class InputHandler;
class Game
{
public:
    Game(uint16_t height = 30, uint16_t width = 20);
    ~Game();
    void TimeTick();
    void UpKeyPressed();
    void DownKeyPressed();
    void LeftKeyPressed();
    void RightKeyPressed();
    void Start();
    void RunInputEvents();
    uint64_t GetScore();
    bool GetIsGameRunning();

    friend class InputHandler;

private:
    void UpdateVirtualScreen();
    void UpdateNextShapeScreen();
    bool CheckMask(uint8_t row, uint8_t column);
    void ClearRight();
    void ClearLeft();
    void ClearUp();
    bool BelowIsEmpty();
    bool RightIsEmpty();
    bool LeftIsEmpty();
    void ClearShape();
    void ClearFullRows();
    bool CheckMaskForNext(uint8_t row, uint8_t column);
    void UpdateScore();
    bool ThereDoesNotAnySpace();
    void GameOver();

private:
    TetrominosGenerator m_Generator;
    Tetrominos *m_CurrentTetrominos;
    Tetrominos *m_NextTetrominos;
    WINDOW *m_GameWindow;
    WINDOW *m_NextTetroWindow;
    uint16_t m_WindowHeight;
    uint16_t m_WindowWidth;
    uint8_t m_NextWindowHeight;
    uint8_t m_NextWindowWidth;
    EnumColor *m_ColorMap;
    uint64_t m_Score;
    bool m_IsGameRunning;
};
#endif