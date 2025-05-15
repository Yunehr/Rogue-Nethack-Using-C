#include "rogue.h"

Level * createLevel(int level) {
    Level * newLevel;
    newLevel = malloc(sizeof(Level)); // Allocate memory for the level

    newLevel->level = level;
    newLevel->numRooms = 3; // Set the number of rooms
    newLevel->rooms = roomsSetup(); // Call the room setup function
    newLevel->tiles = saveLevelPositions(); // Save the level positions

    newLevel->user = playerSetUp(); // Set up the player
    placePlayer(newLevel->rooms, newLevel->user); // Place the player in a random room

    addMonsters(newLevel); // Add monsters to the level

    return newLevel;
}

Room ** roomsSetup() {

    Room ** rooms;
    rooms = malloc(sizeof(Room*) * 6); // Allocate memory for the rooms
    
    for (int x = 0; x < 6; x++) {
        rooms[x] = createRoom(x);
        drawRoom(rooms[x]);
    }
    
    

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