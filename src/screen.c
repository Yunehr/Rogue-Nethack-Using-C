#include "rogue.h"

int screenSetUp() {
    initscr(); // Initialize the window
    noecho(); // Don't echo user input
    keypad(stdscr, TRUE); // Enable keypad input
    refresh(); // Print it on to the real screen

    return 1;
}

int printGameHub(Level * level) {
    
    mvprintw(25, 0, "    Level: %d", level->level);
    printw("    Gold: %d", level->user->gold);
    printw("    Health: %d(%d)", level->user->health, level->user->maxHealth);
    printw("    Attack: %d", level->user->attack);
    printw("    Exp: %d", level->user->exp);
    printw("        ");
    return 1;
}