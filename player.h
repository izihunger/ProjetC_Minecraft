#pragma once

#include <stdlib.h>
#include <stdio.h>
#include "map.h"

#define nbItemMax 32

// Structure : START
typedef struct Player {
    char * name;
    int level;
    int hp;
    int atk;
    int posX;
    int posY;
    int nbItems;
    Item inventory[nbItemMax];
} Player;

// Structure : END

// Function : START
void movePlayer(Bloc ** map, int size, char c);
void spawnPlayer(Bloc ** map, int size);
void spawnVision(Bloc ** map, int size);
void addVision(Bloc ** map, int size, char c, int maxrange);
void setPos(int x, int y);
void setPlayerName(char name[]);
void actionBlocPlayer(Bloc ** map, int size);
Player getPlayer();
void openChest(Bloc ** map);
void displayInventory();