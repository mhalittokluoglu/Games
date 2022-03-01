#include "ScreenHandler.hpp"
#include <ncurses.h>
#include <cstdlib>
#include <cstring>
#include <mutex>

extern std::mutex m;

ScreenHandler::ScreenHandler(uint16_t height, uint16_t width)
    : m_WindowHeight{height}, m_WindowWidth(width)
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
    refresh();
    box(m_GameWindow, 0, 0);
    wrefresh(m_GameWindow);
}

ScreenHandler::~ScreenHandler()
{
    endwin();
}

void ScreenHandler::Start()
{
    m_CurrentTetrominos = m_Generator.GetTetrominos();
    refresh();
    UpdateVirtualScreen();
    wrefresh(m_GameWindow);
}

void ScreenHandler::RunInputEvents()
{
    keypad(m_GameWindow, true);
    while (true)
    {
        int16_t key = wgetch(m_GameWindow);
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
    }
}

void ScreenHandler::TimeTick()
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
        m_CurrentTetrominos = m_Generator.GetTetrominos();
        UpdateVirtualScreen();
    }
}

void ScreenHandler::UpdateVirtualScreen()
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

bool ScreenHandler::CheckMask(uint8_t row, uint8_t column)
{
    return m_CurrentTetrominos->block[row * m_CurrentTetrominos->xSize + column];
}

void ScreenHandler::UpKeyPressed()
{
    ClearShape();
    uint8_t hold = m_CurrentTetrominos->xSize;
    m_CurrentTetrominos->xSize = m_CurrentTetrominos->ySize;
    m_CurrentTetrominos->ySize = hold;
    char *blockCopy = new char[m_CurrentTetrominos->size];
    for (uint8_t i = 0; i < m_CurrentTetrominos->ySize; i++)
    {
        for (uint8_t j = 0; j < m_CurrentTetrominos->xSize; j++)
        {
            blockCopy[j * m_CurrentTetrominos->ySize + i] = m_CurrentTetrominos->block[i * m_CurrentTetrominos->xSize + j];
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
    while (m_CurrentTetrominos->xPos < 1)
        m_CurrentTetrominos->xPos++;
    while (m_CurrentTetrominos->xPos + m_CurrentTetrominos->xSize > m_WindowWidth - 1)
        m_CurrentTetrominos->xPos--;
    UpdateVirtualScreen();
    wrefresh(m_GameWindow);
}

void ScreenHandler::DownKeyPressed()
{
    TimeTick();
}

void ScreenHandler::LeftKeyPressed()
{
    uint8_t xMinSize = 0;
    bool bNotFound = true;
    for (int8_t j = 0; j < m_CurrentTetrominos->xSize && bNotFound; j++)
    {
        for (int8_t i = 0; i < m_CurrentTetrominos->ySize && bNotFound; i++)
        {
            uint8_t index = i * m_CurrentTetrominos->xSize + j;
            if (m_CurrentTetrominos->block[index] == true)
            {
                xMinSize = j;
                bNotFound = false;
            }
        }
    }

    if (m_CurrentTetrominos->xPos + xMinSize > 1)
    {
        ClearRight();
        m_CurrentTetrominos->xPos--;
        UpdateVirtualScreen();
    }
}

void ScreenHandler::RightKeyPressed()
{
    if (RightIsEmpty())
    {
        ClearLeft();
        m_CurrentTetrominos->xPos++;
        UpdateVirtualScreen();
    }
}

void ScreenHandler::ClearRight()
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

void ScreenHandler::ClearLeft()
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

void ScreenHandler::ClearUp()
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

bool ScreenHandler::BelowIsEmpty()
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

bool ScreenHandler::RightIsEmpty()
{
    bool bNotFound = true;
    for (int8_t j = m_CurrentTetrominos->xSize - 1; j >= 0 && bNotFound; j--)
    {
        for (int8_t i = 0; i < m_CurrentTetrominos->ySize; i++)
        {
            if (CheckMask(i, j))
            {
                bNotFound = false;
                wmove(m_GameWindow, m_CurrentTetrominos->yPos, m_CurrentTetrominos->xPos + j + 1);
                uint16_t rightChar = winch(m_GameWindow);
                if (!(rightChar == ' '))
                {
                    return false;
                }
            }
        }
    }
    return true;
}

void ScreenHandler::ClearShape()
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

void ScreenHandler::ClearFullRows()
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
