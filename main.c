#include <ncurses.h>

int screenSetup();
int mapSetup();

int main(void)
{
    screenSetup();
    mapSetup();

    getch();  // Wait for user input
    endwin(); // End ncurses

    return 0;
}

int screenSetup()
{
    initscr();             // Start ncurses
    printw("Hello World"); // Print to the screen
    noecho();              // Don't echo any keypresses
    refresh();             // Refresh the screen is used to update the screen

    return 0;
}

int mapSetup()
{
    // mvprintw(y, x, "string")
    mvprintw(13, 13, "--------");
    mvprintw(14, 13, "|......|");
    mvprintw(15, 13, "|......|");
    mvprintw(16, 13, "|......|");
    mvprintw(17, 13, "|......|");
    mvprintw(18, 13, "--------");

    mvprintw(3, 33, "----------");
    mvprintw(4, 33, "|........|");
    mvprintw(5, 33, "|........|");
    mvprintw(6, 33, "|........|");
    mvprintw(7, 33, "|........|");
    mvprintw(8, 33, "----------");
}