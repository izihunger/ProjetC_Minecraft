#include "player.h"

Player player = {"default", 0, 0, 0};

void spawPlayer(Bloc ** map,int size){
    int i, j;
    do{
        i = rand() % size;
        j = rand() % size;
    }while(!map[i][j].spawnable);
    player.posX = j;
    player.posY = i;
    map[i][j].playerOn = 1;
}

void movePlayer(Bloc ** map, char c){
    switch (c)
    {
    case 'z':
        if(map[player.posY - 1][player.posX].crossable){
            map[player.posY][player.posX].playerOn = 0;
            player.posY --;
            map[player.posY][player.posX].playerOn = 1;
        }
        break;
    case 's':
        if(map[player.posY + 1][player.posX].crossable){
            map[player.posY][player.posX].playerOn = 0;
            player.posY ++;
            map[player.posY][player.posX].playerOn = 1;
        }
        break;
    case 'q':
        if(map[player.posY][player.posX - 1].crossable){
            map[player.posY][player.posX].playerOn = 0;
            player.posX --;
            map[player.posY][player.posX].playerOn = 1;
        }
        break;
    case 'd':
        if(map[player.posY][player.posX + 1].crossable){
            map[player.posY][player.posX].playerOn = 0;
            player.posX ++;
            map[player.posY][player.posX].playerOn = 1;
        }
        break;
    default:
        break;
    }
}