#include "rogue.h"

int main() {
    Player * user;
    int ch;
    Position * newPosition;

    char** level;

    screenSetUp();

    

    mapSetup(); // Call the map setup function

    level = saveLevelPositions(); // Save the level positions

    user = playerSetUp(); // Call the player setup function

    /* main game loop */
    while ((ch = getch()) != 'q') { // Wait for user input
        newPosition = handleInput(ch, user);  
        checkPosition(newPosition, user, level); // Check the new position
    }
    getch(); // Wait for user input

    endwin(); // End the window
    
    return 0;
}

int screenSetUp() {
    initscr(); // Initialize the window
    printw("Hello World!");
    noecho(); // Don't echo user input

    refresh(); // Print it on to the real screen


    return 1;
}


