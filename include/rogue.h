#ifndef ROGUE_H
#define ROGUE_H

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

/*************** Struct Definitions *******************/
typedef struct Level{
    char ** tiles;
    int level;
    int numRooms;
    struct Room ** rooms;
    struct Monster ** monsters;
    int numMonsters;
    struct Player * user;
} Level;

typedef struct Position {
    int x;
    int y;
    // TILE_TYPE tyle;
} Position;

typedef struct Room {
    Position position;
    int height;
    int width;
    struct Door ** doors; 
    int numberOfDoors;
    // Monster ** monsters;
    //Item ** items;
} Room;

typedef struct Door {
    Position * position;
    int connected;;
} Door;

typedef struct Player{
    
    Position * position;
    int maxHealth;
    int health;
    int attack;
    int gold;
    int exp;

    //Room * currentRoom;
} Player;

typedef struct Monster {
    char symbol;
    int health;
    int attack;
    int speed; //might not use right away
    int defense; // might not use right away
    int pathfinding;
    Position * position;
    int alive;

} Monster;

/*************** Global Variables *******************/
#define MAX_HEIGHT 25
#define MAX_WIDTH 100


/* screen functions */
int screenSetUp();
int printGameHub(Level * level);

/* map functions */
Level * createLevel(int level);
Room ** roomsSetup();
char ** saveLevelPositions();
void connectDoors(Level * level);

/* player functions */
Player * playerSetUp();
int placePlayer(Room ** rooms, Player * user);
Position * handleInput(int input, Player * user);
int checkPosition(Position* newPosition, Level * level);
int playerMove(Position * newPosition, Player * user, char ** level);

/* room functions */
Room * createRoom(int grid, int numberOfDoors);
int drawRoom(Room* room);

/* monster functions */
int addMonsters(Level* level);
Monster * selectMonster(int level);
Monster * createMonster(char symbol, int health, int attack, int speed, int defense, int pathfinding);
int killMonster(Monster * monster);
int setStartingPosition(Monster * monster, Room * room);
int moveMonsters(Level * level);
int pathfindingSeek(Position * start, Position * destination);
int pathfindingRandom(Position * start);
Monster * getMonsterAt(Position * position, Monster ** monsters);

/* combat functions */
int combat(Player* player, Monster* monster, int order);





#endif // ROGUE_H