#include "rogue.h"
#include "utils.h"

void addPositionYX(int ** frontier, int frontierCount, int y, int x) {
    frontier[frontierCount][0] = y;
    frontier[frontierCount][1] = x;
}

int checkPos(int y, int x) {
    char temp = mvinch(y, x);

    if (temp == '.' || temp == '|' || temp == '-') {
        return 0; //invalid position
    }
    else{
        return 1;
    }

}

int addNeighbors(int ** frontier, int *** cameFrom, int frontierCount, int y, int x) {
    // north
    if (y-1 >= 0 && x >= 0 && x < MAX_WIDTH && cameFrom[y - 1][x][0] < 0 && checkPos(y-1, x) ==1) {
        addPositionYX(frontier, frontierCount, y - 1, x);
        cameFrom[y - 1][x][0] = y;
        cameFrom[y - 1][x][1] = x;
        frontierCount++;
    }

    // south
    if (y < (MAX_HEIGHT - 1) && x >= 0 && x < MAX_WIDTH && cameFrom[y + 1][x][0] < 0 && checkPos(y+1, x) ==1) {
        addPositionYX(frontier, frontierCount, y + 1, x);
        cameFrom[y + 1][x][0] = y;
        cameFrom[y + 1][x][1] = x;
        frontierCount++;
    }

    // east
    if (x < (MAX_WIDTH - 1) && y >= 0 && y < MAX_HEIGHT && cameFrom[y][x + 1][1] < 0 && checkPos(y, x+1) ==1) {
        addPositionYX(frontier, frontierCount, y, x + 1);
        cameFrom[y][x + 1][0] = y;
        cameFrom[y][x + 1][1] = x;
        frontierCount++;
    }

    // west
    if (x - 1 >= 0 && y > 0 && y < MAX_HEIGHT && cameFrom[y][x - 1][1] < 0 && checkPos(y, x-1) ==1) {
        addPositionYX(frontier, frontierCount, y, x - 1);
        cameFrom[y][x - 1][0] = y;
        cameFrom[y][x - 1][1] = x;
        frontierCount++;
    }

    return frontierCount;
}

int pathFind(Position * start, Position * end) {
    int i, j, y, x;
    int ** frontier = malloc(sizeof(int*) * MAX_HEIGHT * MAX_WIDTH);
    int *** cameFrom = malloc(sizeof(int**) * MAX_HEIGHT);

    int frontierIndex = 0;
    int frontierCount = 0;

    for (i = 0; i < MAX_HEIGHT * MAX_WIDTH; i++) {
        frontier[i] = malloc(sizeof(int) * 2);
    }

    for (i = 0; i < MAX_HEIGHT; i++) {
        cameFrom[i] = malloc(sizeof(int*) * MAX_WIDTH);
        for (j = 0; j < MAX_WIDTH; j++) {
            cameFrom[i][j] = malloc(sizeof(int) * 2);
            cameFrom[i][j][0] = -1; // Initialize to -1
            cameFrom[i][j][1] = -1; // Initialize to -1
        }
    }

    // add start to cameFrom
    cameFrom[start->y][start->x][0] = -9;
    cameFrom[start->y][start->x][1] = -9;

    // add start position to frontier
    addPositionYX(frontier, frontierCount, start->y, start->x);
    frontierCount++;

    while (frontierIndex < frontierCount) {
        y = frontier[frontierIndex][0];
        x = frontier[frontierIndex][1];
        frontierIndex++;

        if (y == end->y && x == end->x) {
            break; // Found the end position
        }
        frontierCount = addNeighbors(frontier, cameFrom, frontierCount, y, x);        
    }

    // Backtrack to find the path
    y = end->y;
    x = end->x;

    while (y != start->y || x != start->x) {
        // Check bounds before accessing cameFrom
    if (y < 0 || y >= MAX_HEIGHT || x < 0 || x >= MAX_WIDTH) {
        break; // Out of bounds, stop to avoid segfault
    }
    int prevY = cameFrom[y][x][0];
    int prevX = cameFrom[y][x][1];
    if (prevY == -1 || prevX == -1) {
        break; // No valid path, stop
    }
    y = prevY;
    x = prevX;

    // Draw the path
    char temp = mvinch(y, x);
    if (temp != '+'){
        mvprintw(y, x, "#");
    }
    else{
        // nothing
    }
    getch(); // for testing purposes
    }

}