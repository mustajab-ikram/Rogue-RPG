#include <ncurses.h>

int screenSetup();

int main(void)
{
    screenSetup();
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