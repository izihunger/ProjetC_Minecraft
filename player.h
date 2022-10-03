#pragma once

#include <stdlib.h>
#include <stdio.h>
#include "map.h"

// Structure : START
typedef struct Player {
    char name[20];
    int level;
    int posX;
    int posY;
} Player;

// Structure : END

// Function : START
void movePlayer(Bloc ** map, char c);
void spawPlayer(Bloc ** map, int size);