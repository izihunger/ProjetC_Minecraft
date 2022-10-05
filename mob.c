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

void moveMob(Bloc ** map, Player player, int size){
    if(abs(mob.posX - player.posX) < size/5 && abs(mob.posY - player.posY) < size/5){
        if(abs(player.posX - mob.posX) > abs(player.posY - mob.posY)){
            if(player.posX > mob.posX){
                if(map[mob.posY][mob.posX + 1].crossable){
                    map[mob.posY][mob.posX].mobOn = 0;
                    mob.posX ++;
                    map[mob.posY][mob.posX].mobOn = 1;
                }
            }
            else{
                if(map[mob.posY][mob.posX - 1].crossable){
                    map[mob.posY][mob.posX].mobOn = 0;
                    mob.posX --;
                    map[mob.posY][mob.posX].mobOn = 1;
                }
            }
        }
        else{
            if(player.posY > mob.posY){
                if(map[mob.posY + 1][mob.posX].crossable){
                    map[mob.posY][mob.posX].mobOn = 0;
                    mob.posY ++;
                    map[mob.posY][mob.posX].mobOn = 1;
                }
            }
            else{
                if(map[mob.posY - 1][mob.posX].crossable){
                    map[mob.posY][mob.posX].mobOn = 0;
                    mob.posY --;
                    map[mob.posY][mob.posX].mobOn = 1;
                }
            }
        }
    }
}