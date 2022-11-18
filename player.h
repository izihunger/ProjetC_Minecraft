#pragma once

#include <stdlib.h>
#include <stdio.h>
#include "map.h"

#define nbItemMax 32

// Structure : START
typedef struct Player {
    char name[20];
    int level;
    int xp;
    int hp;
    int res;
    int atk;
    int posX;
    int posY;
    int nbItems;
    Item inventory[nbItemMax];
} Player;

extern Player player;
// Structure : END

// Function : START
void movePlayer(Bloc ** map, int size, char c);
void spawnPlayer(Bloc ** map, int size);
void spawnVision(Bloc ** map, int size);
void addVision(Bloc ** map, int size, char c, int maxrange);
void setPos(int x, int y);
void actionBlocPlayer(Bloc ** map, int size);
Player getPlayer();
void openChest(Bloc ** map);
void displayInventory();
void manger();
void displayPlayerXP();