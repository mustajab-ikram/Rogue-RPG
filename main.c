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
int handleInput(int input, Player *user);
int checkPosition(int newY, int newX, Player *user);
int playerMove(int y, int x, Player *user);

int main(void)
{
    Player *user;
    char ch;
    screenSetup();
    mapSetup();

    user = playerSetup();

    /* main game loop */
    while ((ch = getch()) != 'q')
    {
        handleInput(ch, user);
    }
    endwin(); // End ncurses

    // Free memory
    free(user);

    return 0;
}

int screenSetup()
{
    initscr();             // Start ncurses
    printw("Hello World"); // Print to the screen
    noecho();              // Don't echo any keypresses
    refresh();             // Refresh the screen is used to update the screen

    return 1;
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

    playerMove(newPlayer->y, newPlayer->x, newPlayer);

    return newPlayer;
}

int handleInput(int input, Player *user)
{
    int newY, newX;
    switch (input)
    {
    // Move up
    case 'w':
    case 'W':
        newY = user->y - 1;
        newX = user->x;
        break;

    // Move down
    case 's':
    case 'S':
        newY = user->y + 1;
        newX = user->x;
        break;

    // Move left
    case 'a':
    case 'A':
        newY = user->y;
        newX = user->x - 1;
        break;

    // Move right
    case 'd':
    case 'D':
        newY = user->y;
        newX = user->x + 1;
        break;

    default:
        break;
    }

    checkPosition(newY, newX, user);
}

/* check what is at next position */
int checkPosition(int newY, int newX, Player *user)
{
    int space;
    switch (mvinch(newY, newX))
    {
    case '.':
        playerMove(newY, newX, user);
        break;

    default:
        move(user->y, user->x);
        break;
    }
}

int playerMove(int y, int x, Player *user)
{
    mvprintw(user->y, user->x, ".");
    user->y = y;
    user->x = x;

    mvprintw(user->y, user->x, "@");
    move(user->y, user->x);
    refresh();

    return 1;
}