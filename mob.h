#pragma once

#include "player.h"

typedef struct Mob {
    char name[20];
    int hp;
    int atk;
    int posX;
    int posY;
} Mob;

void spawnmob(Bloc ** map, int size);