#include "rogue.h"
#include "utils.h"

Level * createLevel(int level) {
    Level * newLevel;
    newLevel = malloc(sizeof(Level)); // Allocate memory for the level

    newLevel->level = level;
    newLevel->numRooms = 3; // Set the number of rooms
    newLevel->rooms = roomsSetup(); // Call the room setup function
    newLevel->tiles = saveLevelPositions(); // Save room locations
    
    //pathFind(newLevel->rooms[0]->doors[1], newLevel->rooms[1]->doors[3]); // Find a path between the rooms
    //newLevel->tiles = saveLevelPositions(); // Save the level positions again after pathfinding
    

    newLevel->user = playerSetUp(); // Set up the player
    placePlayer(newLevel->rooms, newLevel->user); // Place the player in a random room

    addMonsters(newLevel); // Add monsters to the level

    return newLevel;
}

Room ** roomsSetup() {

    Room ** rooms;
    rooms = malloc(sizeof(Room*) * 6); // Allocate memory for the rooms
    
    for (int x = 0; x < 6; x++) {
        rooms[x] = createRoom(x, 4); //hardcoded for now
        drawRoom(rooms[x]);
    }
    
    

    /* connect doors between rooms */
    pathFind(rooms[0]->doors[1]->position, rooms[1]->doors[3]->position);


    return rooms;
}

char ** saveLevelPositions(){
    int x, y;
    char ** positions;
    positions = malloc(sizeof(char*) * MAX_HEIGHT); // Allocate memory for the level

    for (y = 0; y < MAX_HEIGHT; y++) {
        positions[y] = malloc(sizeof(char) * MAX_WIDTH); // Allocate memory for each row
        for (x = 0; x < MAX_WIDTH; x++) {
            positions[y][x] = mvinch(y,x);
        }
    }

    return positions;
}