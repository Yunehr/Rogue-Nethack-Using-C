#include "rogue.h"

Room * createRoom(int grid, int numberOfDoors) {

    Room * newRoom;
    newRoom = malloc(sizeof(Room)); // Allocate memory for the room
    newRoom->numberOfDoors = numberOfDoors;

    switch (grid) {
        case 0:
            newRoom->position.x = 0;
            newRoom->position.y = 0;
            break;
        case 1:
            newRoom->position.x = 33;
            newRoom->position.y = 0;
            break;
        case 2:
            newRoom->position.x = 66;
            newRoom->position.y = 0;
            break;
        case 3:
            newRoom->position.x = 0;
            newRoom->position.y = 14;
            break;
        case 4:
            newRoom->position.x = 33;
            newRoom->position.y = 14;
            break;
        case 5:
            newRoom->position.x = 66;
            newRoom->position.y = 14;
            break;
    }

    newRoom->height = rand() % 6 + 4; // max size 9
    newRoom->width = rand() % 14 + 4; // max size 17


    // offset
    newRoom->position.y += rand() % (9 - newRoom->height + 1);
    newRoom->position.x += rand() % (29 - newRoom->width + 1);
    
    newRoom->doors = malloc(sizeof(Door*) * numberOfDoors);
    
    for (int i = 0; i < numberOfDoors; i++) {
        newRoom->doors[i] = malloc(sizeof(Door)); // Allocate memory for the door
        newRoom->doors[i]->position = malloc(sizeof(Position)); // Allocate memory for the door position
        newRoom->doors[i]->connected = 0; // Initialize the door as not connected
    }

    // top door
    newRoom->doors[0]->position->x = rand() % ((newRoom->width + newRoom->position.x - 1) - (newRoom->position.x + 1)) + (newRoom->position.x + 1);
    newRoom->doors[0]->position->y = newRoom->position.y;

    // right door
    newRoom->doors[1]->position->x = newRoom->position.x + newRoom->width - 1;
    newRoom->doors[1]->position->y = rand() % ((newRoom->height + newRoom->position.y - 1) - (newRoom->position.y + 1)) + (newRoom->position.y + 1);

    // bottom door
    newRoom->doors[2]->position->x = rand() % ((newRoom->width + newRoom->position.x - 1) - (newRoom->position.x + 1)) + (newRoom->position.x + 1);
    newRoom->doors[2]->position->y = newRoom->position.y + newRoom->height - 1;
    
    // left door
    newRoom->doors[3]->position->x = newRoom->position.x;
    newRoom->doors[3]->position->y = rand() % ((newRoom->height + newRoom->position.y - 1) - (newRoom->position.y + 1)) + (newRoom->position.y + 1);

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
    mvprintw(room->doors[0]->position->y, room->doors[0]->position->x, "+"); // top door
    mvprintw(room->doors[1]->position->y, room->doors[1]->position->x, "+"); // bottom door
    mvprintw(room->doors[2]->position->y, room->doors[2]->position->x, "+"); // left door
    mvprintw(room->doors[3]->position->y, room->doors[3]->position->x, "+"); // right door


    return 1;
}

// int connectDoors(Position* door1, Position* door2) {
    
//     Position temp;
//     Position previous;

//     int count = 0;

//     temp.x = door1->x;
//     temp.y = door1->y;
//     previous = temp;

//     while(1){
//         /* step left */
//         if ((abs((temp.x - 1) - door2->x) < abs(temp.x - door2->x)) && (mvinch(temp.y, temp.x - 1) == ' ')) {
//             previous.x = temp.x;
//             temp.x--; 
//         }
//         /* step right */
//         else if ((abs((temp.x + 1) - door2->x) < abs(temp.x - door2->x)) && (mvinch(temp.y, temp.x + 1) == ' ')) {
//             previous.x = temp.x;
//             temp.x++;
//         }
//         /* step up */
//         else if ((abs((temp.y - 1) - door2->y) < abs(temp.y - door2->y)) && (mvinch(temp.y - 1, temp.x) == ' ')) {
//             previous.y = temp.y;
//             temp.y--;
//         }
//         /* step down */
//         else if ((abs((temp.y + 1) - door2->y) < abs(temp.y - door2->y)) && (mvinch(temp.y + 1, temp.x) == ' ')) {
//             previous.y = temp.y;
//             temp.y++;
//         } else{
//             if (count == 0) {
//                 temp = previous;
//                 count++;
//                 continue;
//             }
//             else {
//                 return 0;
//             }
//         }

//         mvprintw(temp.y, temp.x, "#"); // Draw the path

//     }

//     return 1;
// }

