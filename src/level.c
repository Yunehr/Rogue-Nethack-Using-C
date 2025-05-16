#include "rogue.h"
#include "utils.h"

Level * createLevel(int level) {
    Level * newLevel;
    newLevel = malloc(sizeof(Level)); // Allocate memory for the level

    newLevel->level = level;
    newLevel->numRooms = 6; // Set the number of rooms
    newLevel->rooms = roomsSetup(); // Call the room setup function
    connectDoors(newLevel); // Connect the doors between the rooms
    newLevel->tiles = saveLevelPositions(); // Save room locations

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

    return rooms;
}

void connectDoors(Level * level){
    int randomRoom, randomDoor;
    int count;

    for (int i = 0; i < level->numRooms; i++) {
        for (int j = 0; j < level->rooms[i]->numberOfDoors; j++) {
            
            if (level->rooms[i]->doors[j]->connected == 1) {
                continue; // Skip if the door is already connected
            }

            count = 0;

            while (count < 1) {
                randomRoom = rand() % level->numRooms; // Randomly select a room
                randomDoor = rand() % level->rooms[randomRoom]->numberOfDoors; // Randomly select a door
                
                if (level->rooms[randomRoom]->doors[randomDoor]->connected == 1 || randomRoom == i) {
                    count ++; 
                    continue; // Skip if the door is already connected
                }
                
                pathFind(level->rooms[i]->doors[j]->position, level->rooms[randomRoom]->doors[randomDoor]->position); // Connect the doors
                level->rooms[i]->doors[j]->connected = 1; // Mark the door as connected
                level->rooms[randomRoom]->doors[randomDoor]->connected = 1; // Mark the door as connected
                break;
            }
        }
    }
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