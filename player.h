#include <stdlib.h>
#include <stdio.h>

// Structure : START
typedef struct Player {
    char name[20];
    int level;
    int posX;
    int posY;
} Player;

// Structure : END

// Function : START
void movePlayer(char c);