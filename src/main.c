#include "rogue.h"

int main() {
    srand(time(NULL)); // Seed the random number generator

    // Player * user;
    int ch;

    Position * newPosition;

    Level * level;

    screenSetUp();

    level = createLevel(1); // Create the level

    printGameHub(level); // Print the game hub

    move(level->user->position->y, level->user->position->x); // Move the cursor to the player position

    /* main game loop */
    while ((ch = getch()) != 'q') { // Wait for user input
        printGameHub(level); // Print the game hub
        /* Player Movement */
        newPosition = handleInput(ch, level->user);  
        checkPosition(newPosition, level); // Check the new position

        /* Monster Movement */
        moveMonsters(level); // Move the monsters

        /* Move Cursor back to player */
        move(level->user->position->y, level->user->position->x); 
    }

    endwin(); // End the window
    
    return 0;
}


