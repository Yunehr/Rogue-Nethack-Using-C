#include <menu.h>
#include <stdlib.h>

#include "mainMenu.h"

void closeMenu(int numberItems, MENU * menu, ITEM ** items) {
    unpost_menu(menu); 
    free_menu(menu); 
    for (int i = 0; i < numberItems; i++) {
        free_item(items[i]); 
    }
}

int mainMenu(int numberItems, char * choices[]){
    int i, ch, value;
    MENU * menu;
    ITEM ** items = malloc(sizeof(ITEM*) * (numberItems + 1)); 
    ITEM * currentItem;

    for (i = 0; i < numberItems; i++) {
        items[i] = new_item(choices[i], "");
    }
    items[i] = (ITEM *)NULL; // Null terminate the array of items

    menu = new_menu((ITEM **)items); // Create the menu
    post_menu(menu); // Post the menu
    refresh(); 

    //menu loop
    while(true) {
        ch = getch();
        switch(ch) {
            case KEY_DOWN:
                menu_driver(menu, REQ_DOWN_ITEM);
                break;
            case KEY_UP:
                menu_driver(menu, REQ_UP_ITEM);
                break;
            case 10: // Enter key
                currentItem = current_item(menu);
                value = item_index(currentItem);
                closeMenu(numberItems, menu, items);
                return value;
        }
    }
}