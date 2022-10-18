#pragma once

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
void moveMob(Bloc ** map, Player player, int size);
void fightMob(Bloc ** map, Mob mob, Player player, char c);
Mob getMob(int id);
Mob setMob(int id, Mob mob);