#include "rogue.h"
#include "mainMenu.h"

int gameLoop() {
    srand(time(NULL)); 

    int ch;
    Position * newPosition;
    Level * level;

    level = createLevel(1);
    printGameHub(level);

    /* main game loop */
    while ((ch = getch()) != 'q') { 
        printGameHub(level); 
        newPosition = handleInput(ch, level->user);  
        checkPosition(newPosition, level); 
        moveMonsters(level); 
        move(level->user->position->y, level->user->position->x); 

        if (level->user->health <= 0) {
            return -1; // Game over
        }
    }

    return 0;
}

void menuLoop(){
    int choice;
    char * choices[] = {
        "Start Game",
        "End Game",
    };

    while (true) {
        choice = mainMenu(2, choices);

        switch (choice) {
            case START_GAME:
                gameLoop();
                clear();
                // Start the game
                break;
            case END_GAME:
                // End the game
                return;
            default:
                break;
        }
    }
}

int main() {

    screenSetUp();
    menuLoop();    
    endwin(); // End the window
    
    return 0;
}


