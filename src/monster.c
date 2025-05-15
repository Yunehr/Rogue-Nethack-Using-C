#include "rogue.h"

int addMonsters(Level * level) {
    level->monsters = malloc(sizeof(Monster*) * 6); // Allocate memory for the monsters
    level->numMonsters = 0;

    for (int x = 0; x < level->numRooms; x++) {
        if ((rand() % 2) == 0) {
            level->monsters[level->numMonsters] = selectMonster(level->level); 
            setStartingPosition(level->monsters[level->numMonsters], level->rooms[x]); // Set the starting position of the monster
            level->numMonsters++;
        }
    }
}

Monster * selectMonster(int level) {
    int monster;
    switch (level) {
        case 1:
        case 2:
        case 3:
            monster = (rand() % 2) + 1; // 1 or 2
            break;
        case 4:
        case 5:
            monster = (rand() % 2) + 2; // 2 or 3
            break;
        case 6:
            monster = 3;
            break;
    }

    switch (monster) {
        case 1: // Spider
            return createMonster('X', 2, 1, 1, 1, 1);
        case 2: // Goblin
            return createMonster('G', 5, 3, 1, 1, 2);
        case 3:// Troll
            return createMonster('T', 15, 5, 1, 1, 1);
    }
}

Monster * createMonster(char symbol, int health, int attack, int speed, int defense, int pathfinding) {
    Monster * newMonster;
    newMonster = malloc(sizeof(Monster)); // Allocate memory for the monster

    newMonster->symbol = symbol;
    newMonster->health = health;
    newMonster->attack = attack;
    newMonster->speed = speed;
    newMonster->defense = defense;
    newMonster->pathfinding = pathfinding;
    newMonster->alive = 1; // Set the monster as alive

    return newMonster;
}

int killMonster(Monster * monster) {
    mvprintw(monster->position->y, monster->position->x, "."); // Clear the monster from the screen
    monster->alive = 0; // Set the monster as dead

    return 1;
}

int setStartingPosition(Monster * monster, Room * room) {
    monster->position = malloc(sizeof(Position)); // Allocate memory for the position
    
    int x, y;
    x = rand() % (room->width - 2) + room->position.x + 1; // Random x position
    y = rand() % (room->height - 2) + room->position.y + 1; // Random y position

    monster->position->x = x;
    monster->position->y = y;

    mvprintw(monster->position->y, monster->position->x, "%c", monster->symbol); // Draw the monster
    //move(monster->position->y, monster->position->x); // Move the cursor to the monster position

    return 1;
}

int moveMonsters(Level * level) {
    for (int x = 0; x < level->numMonsters; x++) {
        if (level->monsters[x]->alive == 0) {
            continue; // Skip dead monsters
        }

        mvprintw(level->monsters[x]->position->y, level->monsters[x]->position->x, "."); // Clear the monster from the screen
        if (level->monsters[x]->pathfinding == 1) {

            pathfindingRandom(level->monsters[x]->position);

        } else if (level->monsters[x]->pathfinding == 2) {
            pathfindingSeek(level->monsters[x]->position, level->user->position);
        }

        mvprintw(level->monsters[x]->position->y, level->monsters[x]->position->x, "%c", level->monsters[x]->symbol); // Draw the updated monster position
    }
    return 1;
}

int pathfindingSeek(Position * start, Position * destination) {

    mvprintw(start->y, start->x, "."); // Clear the monster from the screen
    /* step left */
    if ((abs((start->x - 1) - destination->x) < abs(start->x - destination->x)) && (mvinch(start->y, start->x - 1) == '.')) {
        start->x--; 
    }
    /* step right */
    else if ((abs((start->x + 1) - destination->x) < abs(start->x - destination->x)) && (mvinch(start->y, start->x + 1) == '.')) {
        start->x++;
    }
    /* step up */
    else if ((abs((start->y - 1) - destination->y) < abs(start->y - destination->y)) && (mvinch(start->y - 1, start->x) == '.')) {
        start->y--;
    }
    /* step down */
    else if ((abs((start->y + 1) - destination->y) < abs(start->y - destination->y)) && (mvinch(start->y + 1, start->x) == '.')) {
        start->y++;

    } else{
        // do nothing
    }
    
    return 1; // Valid move

}

int pathfindingRandom(Position * position) {
    int random = rand() % 5; // Random number between 0 and 4
    switch (random){
        case 0: // step left
            if (mvinch(position->y, position->x - 1) == '.') {
                position->x--;
            } 
            break;
        case 1: // step right
            if (mvinch(position->y, position->x + 1) == '.') {
                position->x++;
            }
            break;
        case 2: // step up
            if (mvinch(position->y - 1, position->x) == '.') {
                position->y--;
            }
            break;
        case 3: // step down
            if (mvinch(position->y + 1, position->x) == '.') {
                position->y++;
            }
            break;
        case 4: // do nothing
        default:
            break;
    }

    //does nothing right now
    
    return 1; // Valid move
}

Monster * getMonsterAt(Position * position, Monster ** monsters) {
    for (int x = 0; x < sizeof(monsters); x++) {
        if (monsters[x]->position->x == position->x && monsters[x]->position->y == position->y) {
            return monsters[x];
        }
    }
    return NULL; // No monster found at the position
}
