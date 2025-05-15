#include "rogue.h"


Player* playerSetUp(){
    Player* newPlayer;
    newPlayer = malloc(sizeof(Player));
    newPlayer->position = malloc(sizeof(Position)); // Allocate memory for the position
    
    newPlayer->position->x = 14;
    newPlayer->position->y = 14;
    newPlayer->health = 20;
    newPlayer->attack = 1;
    newPlayer->gold = 0;
    newPlayer->exp = 0;
    newPlayer->maxHealth = 20;

    return newPlayer;
}

int placePlayer(Room ** rooms, Player * user) {
    int x, y;
    int room = rand() % 6; // Random room number between 0 and 5

    x = rand() % (rooms[room]->width - 2) + rooms[room]->position.x + 1; // Random x position
    y = rand() % (rooms[room]->height - 2) + rooms[room]->position.y + 1; // Random y position

    user->position->x = x;
    user->position->y = y;

    mvprintw(user->position->y, user->position->x, "@"); // Draw the player
    move(user->position->y, user->position->x); // Move the cursor to the player position

    return 1;
}

Position* handleInput(int input, Player * user) {
    Position* newPosition;
    newPosition = malloc(sizeof(Position));
    switch (input) {
        /* move up */
        case 'w':
        case 'W':
            newPosition->y = user->position->y - 1;
            newPosition->x = user->position->x;
            break;
        
        /* move down */
        case 's':
        case 'S':
            newPosition->y = user->position->y + 1;
            newPosition->x = user->position->x;
            break;

        /* move left */
        case 'a':
        case 'A':
            newPosition->y = user->position->y;
            newPosition->x = user->position->x - 1;
            break;

        /* move right */
        case 'd':
        case 'D':
            newPosition->y = user->position->y;
            newPosition->x = user->position->x + 1;
            break;

        default:
            break;
    }

    return newPosition;
    
}

/* Check what is at next position */
int checkPosition(Position* newPosition, Level * level) {
    
    switch (mvinch(newPosition->y, newPosition->x)) {
    /* movable areas */
    case '.': 
    case '+':
    case '#':
        playerMove(newPosition, level->user, level->tiles); // Move the player
        break;
    /* combat */
    case 'X':
    case 'G':
    case 'T':
        combat(level->user, getMonsterAt(newPosition, level->monsters), 1); // player moved towards monster
        break;

    /* wall or cannot move */
    default:
        move(level->user->position->y, level->user->position->x); // Move the cursor to the old position
        break;
    }
}

int playerMove(Position * newPosition, Player * user, char ** level) {
    
    char buffer[8];
    sprintf(buffer, "%c", level[user->position->y][user->position->x]);
    
    mvprintw(user->position->y, user->position->x, "%s", buffer); // Clear the old position
    
    user->position->x = newPosition->x;
    user->position->y = newPosition->y;

    mvprintw(user->position->y, user->position->x, "@"); // Draw the new position
    move(user->position->y, user->position->x); // Move the cursor to the new position

    return 1;
}