#pragma once

#include "player.h"

typedef struct Mob {
    char name[20];
    int hp;
    int atk;
    int posX;
    int posY;
} Mob;

void spawnMob(Bloc ** map, int size);
void moveMob(Bloc ** map, Player player);