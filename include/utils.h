#ifndef UTILS_H
#define UTILS_H

int checkPos(int y, int x);
void addPositionYX(int ** frontier, int frontierCount, int y, int x);
int addNeighbors(int ** frontier, int *** cameFrom, int frontierCount, int y, int x);
int pathFind(Position * start, Position * end);



#endif