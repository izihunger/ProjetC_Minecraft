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
    int nbItems;
    Item inventory[32];
} Player;

// Structure : END

// Function : START
void movePlayer(Bloc ** map, char c);
void spawnPlayer(Bloc ** map, int size);
void setPos(int x, int y);
void setPlayerName(char name[]);
void actionBlocPlayer(Bloc ** map);
Player getPlayer();
void openChest(Bloc ** map);
void displayInventory();