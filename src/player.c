#include "rogue.h"


Player* playerSetUp(){
    Player* newPlayer;
    newPlayer = malloc(sizeof(Player));

    newPlayer->position.x = 14;
    newPlayer->position.y = 14;
    newPlayer->health = 100;

    mvprintw(newPlayer->position.y, newPlayer->position.x, "@"); // Draw the player
    move(newPlayer->position.y, newPlayer->position.x); // Move the cursor to the player position

    return newPlayer;
}

Position* handleInput(int input, Player * user) {
    Position* newPosition;
    newPosition = malloc(sizeof(Position));
    switch (input) {
        /* move up */
        case 'w':
        case 'W':
            newPosition->y = user->position.y - 1;
            newPosition->x = user->position.x;
            break;
        
        /* move down */
        case 's':
        case 'S':
            newPosition->y = user->position.y + 1;
            newPosition->x = user->position.x;
            break;

        /* move left */
        case 'a':
        case 'A':
            newPosition->y = user->position.y;
            newPosition->x = user->position.x - 1;
            break;

        /* move right */
        case 'd':
        case 'D':
            newPosition->y = user->position.y;
            newPosition->x = user->position.x + 1;
            break;

        default:
            break;
    }

    return newPosition;
    
}

/* Check what is at next position */
int checkPosition(Position* newPosition, Player * user, char ** level) {
    
    switch (mvinch(newPosition->y, newPosition->x)) {
    /* movable areas */
    case '.': 
    case '+':
    case '#':
        playerMove(newPosition, user, level); // Move the player
        break;
  
    /* wall or cannot move */
    default:
        move(user->position.y, user->position.x); // Move the cursor to the old position
        break;
    }
}

int playerMove(Position * newPosition, Player * user, char ** level) {
    
    char buffer[8];
    sprintf(buffer, "%c", level[user->position.y][user->position.x]);
    
    mvprintw(user->position.y, user->position.x, "%s", buffer); // Clear the old position
    
    user->position.x = newPosition->x;
    user->position.y = newPosition->y;

    mvprintw(user->position.y, user->position.x, "@"); // Draw the new position
    move(user->position.y, user->position.x); // Move the cursor to the new position

    return 1;
}