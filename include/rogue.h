#ifndef ROGUE_H
#define ROGUE_H

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

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

    Position ** doors; 
    // Monster ** monsters;
    //Item ** items;
} Room;

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

/* screen functions */
int screenSetUp();
int printGameHub(Level * level);

/* map functions */
Level * createLevel(int level);
Room ** roomsSetup();
char ** saveLevelPositions();

/* player functions */
Player * playerSetUp();
int placePlayer(Room ** rooms, Player * user);
Position * handleInput(int input, Player * user);
int checkPosition(Position* newPosition, Level * level);
int playerMove(Position * newPosition, Player * user, char ** level);

/* room functions */
Room * createRoom(int grid);
int drawRoom(Room* room);
int connectDoors(Position* door1, Position* door2);

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