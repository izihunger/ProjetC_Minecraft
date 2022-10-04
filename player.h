#pragma once

#include <stdlib.h>
#include <stdio.h>
#include "map.h"

// Structure : START
typedef struct Player {
    char * name;
    int level;
    int hp;
    int posX;
    int posY;
} Player;

// Structure : END

// Function : START
void movePlayer(Bloc ** map, char c);
void spawPlayer(Bloc ** map, int size);
void setPlayerName(char name[]);
void actionBlocPlayer(Bloc ** map);