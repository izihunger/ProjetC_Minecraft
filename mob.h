#pragma once
#include <unistd.h>

#include "player.h"

typedef struct Mob {
    char name[20];
    int hp;
    int atk;
    int posX;
    int posY;
} Mob;

extern int nbMob;

void spawnMob(Bloc ** map, int size);
void moveMob(Bloc ** map, int size);
int critique();
int esquive();
int fight(Bloc ** map, int size);
Mob getMob(int id);
void setMob(int id, Mob mob);
void mallocMob(int size);