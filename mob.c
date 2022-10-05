#include "mob.h"

Mob mob = {"zombie", 10, 5, 0, 0};

void spawnMob(Bloc ** map, int size){
    int i,j;
    do{
        i = rand() % size;
        j = rand() % size;
    }while(!map[i][j].spawnable && map[i][j].chest);
    mob.posX = j;
    mob.posY = i;
    map[i][j].mobOn = 1;
}

void moveMob(Bloc ** map, Player player){
    if(abs(mob.posX - player.posX) < )
}