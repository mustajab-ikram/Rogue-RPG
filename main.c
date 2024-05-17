#include <ncurses.h>
#include <stdlib.h>

typedef struct Player
{
    int x;
    int y;
    int health;

} Player;

int screenSetup();
int mapSetup();
Player *playerSetup();

int main(void)
{
    Player *user;
    char ch;
    screenSetup();
    mapSetup();

    user = playerSetup();

    while ((ch = getch()) != 'q')
    {
    }
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

Player *playerSetup()
{
    Player *newPlayer = (Player *)malloc(sizeof(Player));

    newPlayer->x = 14;
    newPlayer->y = 14;
    newPlayer->health = 20;

    mvprintw(newPlayer->y, newPlayer->x, "@");
    move(newPlayer->y, newPlayer->x);

    return newPlayer;
}