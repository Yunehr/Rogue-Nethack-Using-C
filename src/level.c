#include "rogue.h"

Room ** mapSetup() {

    Room ** rooms;
    rooms = malloc(sizeof(Room*) * 6); // Allocate memory for the rooms

    rooms [0] = createRoom(13, 13, 6, 8);
    rooms [1] = createRoom(40, 2, 6, 8);
    rooms [2] = createRoom(40, 10, 6, 12);

    drawRoom(rooms[0]);
    drawRoom(rooms[1]);
    drawRoom(rooms[2]);

    /* connect doors between rooms */
    connectDoors(rooms[0]->doors[1], rooms[2]->doors[3]);
    connectDoors(rooms[0]->doors[0], rooms[1]->doors[2]);


    return rooms;
}

char ** saveLevelPositions(){
    int x, y;
    char ** positions;
    positions = malloc(sizeof(char*) * 25); // Allocate memory for the level

    for (y = 0; y < 25; y++) {
        positions[y] = malloc(sizeof(char) * 100); // Allocate memory for each row
        for (x = 0; x < 100; x++) {
            positions[y][x] = mvinch(y,x);
        }
    }

    return positions;
}