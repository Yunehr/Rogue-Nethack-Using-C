#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <menu.h>

enum {
    START_GAME,
    END_GAME,
};

void closeMenu(int numberItems, MENU * menu, ITEM ** items);
int mainMenu(int numberItems, char * choices[]);




#endif