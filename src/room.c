#include "rogue.h"

Room * createRoom(int x, int y, int height, int width) {

    Room * newRoom;
    newRoom = malloc(sizeof(Room)); // Allocate memory for the room

    // basic room setup
    newRoom->position.x = x;
    newRoom->position.y = y;
    newRoom->height = height;
    newRoom->width = width;

    // randomize door positions
    srand(time(NULL)); // Seed the random number generator

    newRoom->doors = malloc(sizeof(Position) * 4); // Allocate memory for the doors

    // top door
    newRoom->doors[0] = malloc(sizeof(Position)); // Allocate memory for the door
    newRoom->doors[0]->x = rand() % ((width + x - 1) - (x + 1)) + (x + 1);
    newRoom->doors[0]->y = y;

    // right door
    newRoom->doors[1] = malloc(sizeof(Position)); // Allocate memory for the door
    newRoom->doors[1]->x = x + width - 1;
    newRoom->doors[1]->y = rand() % ((height + y - 1) - (y + 1)) + (y + 1);

    // bottom door
    newRoom->doors[2] = malloc(sizeof(Position)); // Allocate memory for the door
    newRoom->doors[2]->x = rand() % ((width + x - 1) - (x + 1)) + (x + 1);
    newRoom->doors[2]->y = y + height - 1;
    
    // left door
    newRoom->doors[3] = malloc(sizeof(Position)); // Allocate memory for the door
    newRoom->doors[3]->x = x;
    newRoom->doors[3]->y = rand() % ((height + y - 1) - (y + 1)) + (y + 1);

    return newRoom;
}

int drawRoom(Room * room) {
    int x, y;

    /* Draw Top and Bottom*/
    for (x = room->position.x; x < room->position.x + room->width; x++) {
        mvprintw(room->position.y, x, "-"); // top
        mvprintw(room->position.y + room->height - 1, x, "-"); // bottom
    }

    /* floors and side walls*/
    for (y = room->position.y + 1; y < room->position.y + room->height -1; y++) {
        mvprintw(y, room->position.x, "|"); // left
        mvprintw(y, room->position.x + room->width - 1, "|"); // right
        for (x = room->position.x + 1; x < room->position.x + room->width - 1; x++) {
            mvprintw(y, x, "."); // floor
        }
    }

    /* Draw doors */
    mvprintw(room->doors[0]->y, room->doors[0]->x, "+"); // top door
    mvprintw(room->doors[1]->y, room->doors[1]->x, "+"); // bottom door
    mvprintw(room->doors[2]->y, room->doors[2]->x, "+"); // left door
    mvprintw(room->doors[3]->y, room->doors[3]->x, "+"); // right door


    return 1;
}

int connectDoors(Position* door1, Position* door2) {
    
    Position temp;
    Position previous;

    int count = 0;

    temp.x = door1->x;
    temp.y = door1->y;
    previous = temp;

    while(1){
        /* step left */
        if ((abs((temp.x - 1) - door2->x) < abs(temp.x - door2->x)) && (mvinch(temp.y, temp.x - 1) == ' ')) {
            previous.x = temp.x;
            temp.x--; 
        }
        /* step right */
        else if ((abs((temp.x + 1) - door2->x) < abs(temp.x - door2->x)) && (mvinch(temp.y, temp.x + 1) == ' ')) {
            previous.x = temp.x;
            temp.x++;
        }
        /* step up */
        else if ((abs((temp.y - 1) - door2->y) < abs(temp.y - door2->y)) && (mvinch(temp.y - 1, temp.x) == ' ')) {
            previous.y = temp.y;
            temp.y--;
        }
        /* step down */
        else if ((abs((temp.y + 1) - door2->y) < abs(temp.y - door2->y)) && (mvinch(temp.y + 1, temp.x) == ' ')) {
            previous.y = temp.y;
            temp.y++;
        } else{
            if (count == 0) {
                temp = previous;
                count++;
                continue;
            }
            else {
                return 0;
            }
        }

        mvprintw(temp.y, temp.x, "#"); // Draw the path

    }

    return 1;
}

