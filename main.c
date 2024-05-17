#include <ncurses.h>
#include <stdlib.h>

typedef struct Room
{
    int x;
    int y;
    int width;
    int height;

} Room;

typedef struct Player
{
    int x;
    int y;
    int health;

} Player;

int screenSetup();
Room **mapSetup();
Player *playerSetup();
int handleInput(int input, Player *user);
int checkPosition(int newY, int newX, Player *user);
int playerMove(int y, int x, Player *user);
int drawRoom(Room *room);

/* room functions */
Room *createRoom(int x, int y, int width, int height);

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

Room **mapSetup()
{
    Room **rooms;
    rooms = malloc(sizeof(Room) * 6);

    rooms[0] = createRoom(13, 13, 6, 8);
    drawRoom(rooms[0]);
    rooms[1] = createRoom(33, 3, 10, 6);
    drawRoom(rooms[1]);
    rooms[2] = createRoom(45, 15, 8, 6);
    drawRoom(rooms[2]);
}

Room *createRoom(int x, int y, int width, int height)
{
    Room *newRoom;
    newRoom = (Room *)malloc(sizeof(Room));

    newRoom->x = x;
    newRoom->y = y;
    newRoom->width = width;
    newRoom->height = height;

    return newRoom;
}

int drawRoom(Room *room)
{
    int x;
    int y;
    int width = room->width;
    int height = room->height;

    // Draw the top and bottom walls
    for (x = room->x; x < room->x + width; x++)
    {
        mvprintw(room->y, x, "-");
        // 2 points are y2 - y1 + 1 heigh
        mvprintw(room->y + height - 1, x, "-");
    }

    // Draw the side walls and floor
    for (y = room->y + 1; y < room->y + height - 1; y++)
    {
        mvprintw(y, room->x, "|");
        // 2 points are x2 - x1 + 1 wide
        mvprintw(y, room->x + width - 1, "|");
        for (x = room->x + 1; x < room->x + width - 1; x++)
        {
            mvprintw(y, x, ".");
        }
    }

    return 1;
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