#include "Game.hpp"
#include <ncurses.h>
#include <cstdlib>
#include <cstring>
#include <mutex>

extern std::mutex m;

Game::Game(uint16_t height, uint16_t width)
    : m_WindowHeight{height}, m_WindowWidth(width), m_Score {0}, 
        m_IsGameRunning { false }
{
    m_ColorMap = new EnumColor[height * width];
    memset(m_ColorMap, 0, sizeof(EnumColor) * width * height);
    initscr();
    noecho();
    cbreak();
    curs_set(0);

    if (!has_colors)
    {
        printw("Your Terminal does not support Colors!");
        exit(1);
    }
    start_color();
    // ColorPairs
    init_pair(BLACK, COLOR_BLACK, COLOR_BLACK);
    init_pair(RED, COLOR_BLACK, COLOR_RED);
    init_pair(GREEN, COLOR_BLACK, COLOR_GREEN);
    init_pair(YELLOW, COLOR_BLACK, COLOR_YELLOW);
    init_pair(BLUE, COLOR_BLACK, COLOR_BLUE);
    init_pair(MAGENTA, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(CYAN, COLOR_BLACK, COLOR_CYAN);
    init_pair(WHITE, COLOR_BLACK, COLOR_WHITE);

    m_GameWindow = newwin(height, width, 0, 0);
    m_NextWindowHeight = 8;
    m_NextWindowWidth = 8;
    m_NextTetroWindow = newwin(m_NextWindowHeight, m_NextWindowWidth, 0, width + 5);
    refresh();
    box(m_GameWindow, 0, 0);
    box (m_NextTetroWindow, 0, 0);
    wrefresh(m_GameWindow);
    wrefresh(m_NextTetroWindow);
    UpdateScore();
}

Game::~Game()
{
    endwin();
}

void Game::Start()
{
    m_IsGameRunning = true;
    m_NextTetrominos = m_Generator.GetTetrominos();
    m_CurrentTetrominos = m_Generator.GetTetrominos();
    while (m_CurrentTetrominos->shape == Z_SHAPE or m_CurrentTetrominos->shape == REVERSE_Z_SHAPE)
    {
        delete m_CurrentTetrominos;
        m_CurrentTetrominos = m_Generator.GetTetrominos();
    }
    UpdateNextShapeScreen();
    UpdateVirtualScreen();
    wrefresh(m_GameWindow);
    refresh();
}

void Game::RunInputEvents()
{
    keypad(m_GameWindow, true);
    while (m_IsGameRunning)
    {
        int16_t key = wgetch(m_GameWindow);
        m.lock();
        if (key == KEY_UP)
        {
            UpKeyPressed();
        }
        else if (key == KEY_DOWN)
        {
            DownKeyPressed();
        }
        else if (key == KEY_RIGHT)
        {
            RightKeyPressed();
        }
        else if (key == KEY_LEFT)
        {
            LeftKeyPressed();
        }
        wrefresh(m_GameWindow);
        m.unlock();
    }
}

void Game::TimeTick()
{
    if (BelowIsEmpty())
    {
        ClearUp();
        m_CurrentTetrominos->yPos++;
        UpdateVirtualScreen();
        wrefresh(m_GameWindow);
    }
    else
    {
        ClearFullRows();
        delete m_CurrentTetrominos;
        m_CurrentTetrominos = m_NextTetrominos;
        m_NextTetrominos = m_Generator.GetTetrominos();
        if (ThereDoesNotAnySpace())
        {
            GameOver();
        }
        else
        {
            UpdateNextShapeScreen();
            UpdateVirtualScreen();
        }
    }
}

void Game::UpdateVirtualScreen()
{
    // wprintw(m_GameWindow, "%d", m_CurrentTetrominos->color);
    wmove(m_GameWindow, m_CurrentTetrominos->yPos, m_CurrentTetrominos->xPos);
    for (uint8_t i = 0; i < m_CurrentTetrominos->ySize; i++)
    {
        for (uint8_t j = 0; j < m_CurrentTetrominos->xSize; j++)
        {
            wmove(m_GameWindow, m_CurrentTetrominos->yPos + i, m_CurrentTetrominos->xPos + j);
            if (CheckMask(i, j))
            {
                wattron(m_GameWindow, COLOR_PAIR(m_CurrentTetrominos->color));
                int16_t colorMapIndex = (m_CurrentTetrominos->yPos + i) * m_WindowWidth + m_CurrentTetrominos->xPos + j;
                m_ColorMap[colorMapIndex] = m_CurrentTetrominos->color;
                wprintw(m_GameWindow, "X");
                wattroff(m_GameWindow, COLOR_PAIR(m_CurrentTetrominos->color));
            }
        }
    }
}

bool Game::CheckMask(uint8_t row, uint8_t column)
{
    return m_CurrentTetrominos->block[row * m_CurrentTetrominos->xSize + column];
}

bool Game::CheckMaskForNext(uint8_t row, uint8_t column)
{
    return m_NextTetrominos->block[row * m_NextTetrominos->xSize + column];
}

void Game::UpKeyPressed()
{
    ClearShape();
    uint8_t hold = m_CurrentTetrominos->xSize;
    m_CurrentTetrominos->xSize = m_CurrentTetrominos->ySize;
    m_CurrentTetrominos->ySize = hold;
    char *currenPositionblock = new char [m_CurrentTetrominos->size];
    char *blockCopy = new char[m_CurrentTetrominos->size];
    for (uint8_t i = 0; i < m_CurrentTetrominos->ySize; i++)
    {
        for (uint8_t j = 0; j < m_CurrentTetrominos->xSize; j++)
        {
            blockCopy[j * m_CurrentTetrominos->ySize + i] = m_CurrentTetrominos->block[i * m_CurrentTetrominos->xSize + j];
            currenPositionblock[i * m_CurrentTetrominos->xSize + j] = m_CurrentTetrominos->block[i * m_CurrentTetrominos->xSize + j];
        }
    }
    for (uint8_t i = 0; i < m_CurrentTetrominos->ySize; i++)
    {
        for (uint8_t j = 0; j < m_CurrentTetrominos->xSize; j++)
        {
            m_CurrentTetrominos->block[i * m_CurrentTetrominos->xSize + m_CurrentTetrominos->ySize - j - 1] = blockCopy[i * m_CurrentTetrominos->xSize + j];
        }
    }
    delete[] blockCopy;

    bool bValidForRatate = true;
    for (uint8_t i = 0; i < m_CurrentTetrominos->ySize && bValidForRatate; i++)
    {
        for (uint8_t j = 0; j < m_CurrentTetrominos->xSize && bValidForRatate; j++)
        {
            if (CheckMask(i, j))
            {
                wmove(m_GameWindow, m_CurrentTetrominos->yPos + i, m_CurrentTetrominos->xPos + j);
                char charOnShape = winch(m_GameWindow);
                if (charOnShape != ' ')
                {
                    bValidForRatate = false;
                }
            }
        }
    }
    
    if (!bValidForRatate)
    {
        for (uint8_t i = 0; i < m_CurrentTetrominos->ySize; i++)
        {
            for (uint8_t j = 0; j < m_CurrentTetrominos->xSize; j++)
            {
                m_CurrentTetrominos->block[i * m_CurrentTetrominos->xSize + j] = currenPositionblock[i * m_CurrentTetrominos->xSize + j];
            }
        }
    }
    delete [] currenPositionblock;
    UpdateVirtualScreen();
    wrefresh(m_GameWindow);
}

void Game::DownKeyPressed()
{
    TimeTick();
}

void Game::LeftKeyPressed()
{
    if (LeftIsEmpty())
    {
        ClearRight();
        m_CurrentTetrominos->xPos--;
        UpdateVirtualScreen();
    }
}

void Game::RightKeyPressed()
{
    if (RightIsEmpty())
    {
        ClearLeft();
        m_CurrentTetrominos->xPos++;
        UpdateVirtualScreen();
    }
}

void Game::ClearRight()
{
    bool bNotFound;
    for (int8_t i = 0; i < m_CurrentTetrominos->ySize; i++)
    {
        bNotFound = true;
        for (int8_t j = m_CurrentTetrominos->xSize - 1; j >= 0 && bNotFound; j--)
        {
            if (CheckMask(i, j))
            {
                wmove(m_GameWindow, m_CurrentTetrominos->yPos + i, m_CurrentTetrominos->xPos + j);
                m_ColorMap[(m_CurrentTetrominos->yPos + i) * m_WindowWidth + m_CurrentTetrominos->xPos + j] = BLACK;
                wprintw(m_GameWindow, " ");
                bNotFound = false;
            }
        }
    }
}

void Game::ClearLeft()
{
    bool bNotFound;
    for (int8_t i = 0; i < m_CurrentTetrominos->ySize; i++)
    {
        bNotFound = true;
        for (int8_t j = 0; j < m_CurrentTetrominos->xSize && bNotFound; j++)
        {
            if (CheckMask(i, j))
            {
                wmove(m_GameWindow, m_CurrentTetrominos->yPos + i, m_CurrentTetrominos->xPos + j);
                m_ColorMap[(m_CurrentTetrominos->yPos + i) * m_WindowWidth + m_CurrentTetrominos->xPos + j] = BLACK;
                wprintw(m_GameWindow, " ");
                bNotFound = false;
            }
        }
    }
}

void Game::ClearUp()
{
    bool bNotFound;
    for (int8_t j = 0; j < m_CurrentTetrominos->xSize; j++)
    {
        bNotFound = true;
        for (int8_t i = 0; i < m_CurrentTetrominos->ySize && bNotFound; i++)
        {
            if (CheckMask(i, j))
            {
                wmove(m_GameWindow, m_CurrentTetrominos->yPos + i, m_CurrentTetrominos->xPos + j);
                m_ColorMap[(m_CurrentTetrominos->yPos + i) * m_WindowWidth + m_CurrentTetrominos->xPos + j] = BLACK;
                wprintw(m_GameWindow, " ");
                bNotFound = false;
            }
        }
    }
}

bool Game::BelowIsEmpty()
{
    bool written = false;
    for (int8_t j = 0; j < m_CurrentTetrominos->xSize; j++)
    {
        bool bNotFound = true;
        for (int8_t i = m_CurrentTetrominos->ySize - 1; i >= 0 && bNotFound; i--)
        {
            if (CheckMask(i, j))
            {
                bNotFound = false;
                wmove(m_GameWindow, m_CurrentTetrominos->yPos + i + 1, m_CurrentTetrominos->xPos + j);
                uint16_t belowChar = winch(m_GameWindow);
                if (!(belowChar == ' '))
                {
                    return false;
                }
            }
        }
    }
    return true;
}

bool Game::RightIsEmpty()
{
    bool bFoundedRows[4] = { 0 };
    for (int8_t j = m_CurrentTetrominos->xSize - 1; j >= 0; j--)
    {
        for (int8_t i = 0; i < m_CurrentTetrominos->ySize; i++)
        {
            if (CheckMask(i, j))
            {
                if (bFoundedRows[i] != true)
                {
                    bFoundedRows[i] = true;
                    wmove(m_GameWindow, m_CurrentTetrominos->yPos + i, m_CurrentTetrominos->xPos + j + 1);
                    uint16_t rightChar = winch(m_GameWindow);
                    if (!(rightChar == ' '))
                    {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

bool Game::LeftIsEmpty()
{
    bool bFoundedRows[4] = { 0 };
    for (int8_t j = 0; j < m_CurrentTetrominos->xSize; j++)
    {
        for (int8_t i = 0; i < m_CurrentTetrominos->ySize; i++)
        {
            if (CheckMask(i, j))
            {
                if (bFoundedRows[i] != true)
                {
                    bFoundedRows[i] = true;
                    wmove(m_GameWindow, m_CurrentTetrominos->yPos + i, m_CurrentTetrominos->xPos + j - 1);
                    uint16_t rightChar = winch(m_GameWindow);
                    if (!(rightChar == ' '))
                    {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

void Game::ClearShape()
{
    for (int8_t i = 0; i < m_CurrentTetrominos->ySize; i++)
    {
        for (int8_t j = 0; j < m_CurrentTetrominos->xSize; j++)
        {
            if (m_CurrentTetrominos->block[i * m_CurrentTetrominos->xSize + j])
            {
                wmove(m_GameWindow, m_CurrentTetrominos->yPos + i, m_CurrentTetrominos->xPos + j);
                m_ColorMap[(m_CurrentTetrominos->yPos + i) * m_WindowWidth + m_CurrentTetrominos->xPos + j] = BLACK;
                wprintw(m_GameWindow, " ");
            }
        }
    }
}

void Game::ClearFullRows()
{
    bool *bFullRows = new bool[m_WindowHeight]{0};
    int16_t fullRowSize = 0;
    int16_t *fullRowSizes = new int16_t[m_WindowHeight]{0};
    bool bFullRowExist = false;
    for (int16_t i = m_WindowHeight -2; i > 0; i--)
    {
        bool bFull = true;
        for (int16_t j = 1; j < m_WindowWidth - 1 && bFull; j++)
        {
            wmove(m_GameWindow, i, j);
            int16_t currentChar = winch(m_GameWindow);
            if (currentChar == ' ')
            {
                bFull = false;
            }
        }
        if (bFull)
        {
            bFullRowExist = true;
            fullRowSize++;
            bFullRows[i] = true;
        }
        fullRowSizes[i] = fullRowSize;
    }
    if (bFullRowExist)
    {
        m_Score += fullRowSize;
        UpdateScore();
        for (int16_t i = m_WindowHeight - 2; i > 0; i--)
        {
            for (int16_t j = 1; j < m_WindowWidth - 1; j++)
            {
                int16_t charAbove = ' ';
                EnumColor colorAbove = BLACK;
                if (i - fullRowSizes[i] > 2)
                {
                    wmove(m_GameWindow, i - fullRowSize - fullRowSizes[i] + 1, j);
                    charAbove = winch(m_GameWindow);
                    int16_t colorMapIndex = (i - fullRowSize - fullRowSizes[i] + 1) * m_WindowWidth + j;
                    colorAbove = m_ColorMap[colorMapIndex];
                }
                wmove(m_GameWindow, i, j);
                wattron(m_GameWindow, COLOR_PAIR(colorAbove));
                wprintw(m_GameWindow, "%c", charAbove);
                int16_t colorMapIndex = i  * m_WindowWidth + j;
                m_ColorMap[colorMapIndex] = colorAbove;
                wattroff(m_GameWindow, COLOR_PAIR(colorAbove));
            }
        }
    
    }
    delete[] bFullRows;
}

void Game::UpdateNextShapeScreen()
{
    for (uint8_t i = 1; i < m_NextWindowHeight - 1; i++)
    {
        for (uint8_t j = 1; j < m_NextWindowWidth - 1; j++)
        {
            wmove(m_NextTetroWindow, i, j);
            wprintw(m_NextTetroWindow, " ");
        }
    }
    for (uint8_t i = 0; i < m_NextTetrominos->ySize; i++)
    {
        for (uint8_t j = 0; j < m_NextTetrominos->xSize; j++)
        {
            if (CheckMaskForNext(i, j))
            {
                wmove(m_NextTetroWindow, 2 + i, 2 + j);
                wattron(m_NextTetroWindow, COLOR_PAIR(m_NextTetrominos->color));
                wprintw(m_NextTetroWindow, "X");
                wattroff(m_NextTetroWindow, COLOR_PAIR(m_NextTetrominos->color));
            }
        }
    }
    wrefresh(m_NextTetroWindow);
}

void Game::UpdateScore()
{
    move(m_WindowHeight - 5, m_WindowWidth + 10);
    printw("Score: %d", m_Score);
    refresh();
}

uint64_t Game::GetScore()
{
    return m_Score;
}

bool Game::ThereDoesNotAnySpace()
{
    bool bResult = false;
    for (uint8_t i = 0; i < m_CurrentTetrominos->ySize; i++)
    {
        for (uint8_t j = 0; j < m_CurrentTetrominos->xSize; j++)
        {
            if (CheckMask(i, j))
            {
                wmove(m_GameWindow, m_CurrentTetrominos->yPos + i, m_CurrentTetrominos->xPos + j);
                char charOnWindow = winch(m_GameWindow);
                if (charOnWindow != ' ')
                {
                    bResult = true;
                }
            }
        }
    }
    return bResult;
}


void Game::GameOver()
{
    m_IsGameRunning = false;
    wmove(m_GameWindow, m_WindowHeight/2 - 1, m_WindowWidth/2 - 5);
    wprintw(m_GameWindow, "   GAME OVER   ");
    wmove(m_GameWindow, m_WindowHeight/2, m_WindowWidth/2 - 5);
    wprintw(m_GameWindow, "Pres q to exit");
    wrefresh(m_GameWindow);
    char key = wgetch(m_GameWindow);
    while (key != 'q')
    {
        key = wgetch(m_GameWindow);
    }
}

bool Game::GetIsGameRunning()
{
    return m_IsGameRunning;
}