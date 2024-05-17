#include <ncurses.h>
#include <stdlib.h>

typedef struct Position
{
    int x;
    int y;
    // TILE_TYPE tile;
} Position;
typedef struct Room
{
    Position position;
    int width;
    int height;

} Room;

typedef struct Player
{
    Position position;
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

    newRoom->position.x = x;
    newRoom->position.y = y;
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
    for (x = room->position.x; x < room->position.x + width; x++)
    {
        mvprintw(room->position.y, x, "-");
        // 2 points are y2 - y1 + 1 heigh
        mvprintw(room->position.y + height - 1, x, "-");
    }

    // Draw the side walls and floor
    for (y = room->position.y + 1; y < room->position.y + height - 1; y++)
    {
        mvprintw(y, room->position.x, "|");
        // 2 points are x2 - x1 + 1 wide
        mvprintw(y, room->position.x + width - 1, "|");
        for (x = room->position.x + 1; x < room->position.x + width - 1; x++)
        {
            mvprintw(y, x, ".");
        }
    }

    return 1;
}

Player *playerSetup()
{
    Player *newPlayer = (Player *)malloc(sizeof(Player));

    newPlayer->position.x = 14;
    newPlayer->position.y = 14;
    newPlayer->health = 20;

    playerMove(newPlayer->position.y, newPlayer->position.x, newPlayer);

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
        newY = user->position.y - 1;
        newX = user->position.x;
        break;

    // Move down
    case 's':
    case 'S':
        newY = user->position.y + 1;
        newX = user->position.x;
        break;

    // Move left
    case 'a':
    case 'A':
        newY = user->position.y;
        newX = user->position.x - 1;
        break;

    // Move right
    case 'd':
    case 'D':
        newY = user->position.y;
        newX = user->position.x + 1;
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
        move(user->position.y, user->position.x);
        break;
    }
}

int playerMove(int y, int x, Player *user)
{
    mvprintw(user->position.y, user->position.x, ".");
    user->position.y = y;
    user->position.x = x;

    mvprintw(user->position.y, user->position.x, "@");
    move(user->position.y, user->position.x);
    refresh();

    return 1;
}