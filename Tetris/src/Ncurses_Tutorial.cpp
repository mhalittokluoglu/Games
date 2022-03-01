#include <ncurses.h>

int main()
{
    initscr();
    cbreak();
    noecho();
    curs_set(0);

    // if (!has_colors())
    // {
    //     printw("Terminal does not support colors");
    //     getch();
    //     return -1;
    // }
    // start_color();

    init_pair(1, COLOR_CYAN, COLOR_CYAN);

    // attron(COLOR_PAIR(1));
    // printw("$$$$$$");
    // attroff(COLOR_PAIR(1));
    // printw("\n  ");
    // attron(COLOR_PAIR(1));
    // printw("$$");
    // attroff(COLOR_PAIR(1));

    // int height, width, start_y, start_x;
    // height = 10;
    // width = 20;
    // start_y = start_x = 10;

    // WINDOW *win = newwin(height, width, start_y, start_x);
    // refresh();

    // box(win, 0, 0);
    // wprintw(win, "this is a box");
    // wrefresh(win);

    WINDOW *inputwin = newwin(10, 20, 5, 5);
    box(inputwin, 0, 0);
    refresh();
    wrefresh(inputwin);

    keypad(inputwin, true);
    int c = wgetch(inputwin);
    if (c == KEY_UP)
    {
        wmove(inputwin, 1, 1);
        wprintw(inputwin, "UP   ");
        wrefresh(inputwin);
    }
    else if (c == KEY_DOWN)
    {
        wmove(inputwin, 1, 1);
        wprintw(inputwin, "DOWN ");
        wrefresh(inputwin);
    }
    else if (c == KEY_LEFT)
    {
        wmove(inputwin, 1, 1);
        wprintw(inputwin, "LEFT ");
        wrefresh(inputwin);
    }
    else if (c == KEY_RIGHT)
    {
        wmove(inputwin, 1, 1);
        wprintw(inputwin, "RIGHT");
        wrefresh(inputwin);
    }
    else
    {
        wmove(inputwin, 1, 1);
        wprintw(inputwin, "Pressed %c", c);
        wrefresh(inputwin);
    }


    getch();

    endwin();
}