#ifndef _SCREENHANDLER_HPP_
#define _SCREENHANDLER_HPP_
#include <ncurses.h>
#include "../Tetrominos/TetrominosGenerator.hpp"
class InputHandler;
class ScreenHandler
{
public:
    ScreenHandler(uint16_t height = 30, uint16_t width = 20);
    ~ScreenHandler();
    void TimeTick();
    void UpKeyPressed();
    void DownKeyPressed();
    void LeftKeyPressed();
    void RightKeyPressed();
    void Start();

    friend class InputHandler;

private:
    void UpdateVirtualScreen();
    bool CheckMask(uint8_t i, uint8_t j);
    void ClearRight();
    void ClearLeft();
    void ClearUp();
    bool BelowIsEmpty();
    bool RightIsEmpty();
    void ClearShape();
    void ClearFullRows();

private:
    TetrominosGenerator m_Generator;
    Tetrominos *m_CurrentTetrominos;
    WINDOW *m_GameWindow;
    uint16_t m_WindowHeight;
    uint16_t m_WindowWidth;
    EnumColor *m_ColorMap;
};
#endif