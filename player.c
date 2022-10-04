#include "player.h"

/*
const Bloc Dirt = {0, "\033[31m#", 1, 1, 1, 0};
const Bloc Stone = {1, "\033[37m#", 1, 1, 1, 0};
const Bloc Water = {2, "\033[34m~", 0, 0, 1, 0};
const Bloc Tree = {3, "\033[32mT", 0, 0, 0, 0};
*/

Player player = {"default", 0, 50, 0, 0};

void spawnPlayer(Bloc ** map,int size){
    int i, j;
    do{
        i = rand() % size;
        j = rand() % size;
    }while(!map[i][j].spawnable);
    player.posX = j;
    player.posY = i;
    map[i][j].playerOn = 1;
}

void setPos(int x, int y){
    player.posX = x;
    player.posY = y;
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
    case 't':
        //actionBlocPlayer(map);
        break;
    default:
        break;
    }
}
void setPlayerName(char * name){
    player.name = name;
}

/*
// Modif map : tree repere puis detruit mais display ne change pas
void actionBlocPlayer(Bloc ** map){
    if(map[player.posY-1][player.posX].id == 3 || map[player.posY+1][player.posX].id == 3 || map[player.posY][player.posX-1].id == 3 || map[player.posY][player.posX+1].id == 3){
        printf("Il y a un arbre à casser\n");
        if(map[player.posY-1][player.posX].id == 3){
            map[player.posY-1][player.posX] = Dirt;
        }
        else if(map[player.posY+1][player.posX].id == 3){
            map[player.posY+1][player.posX] = Dirt;
        }
        else if(map[player.posY][player.posX-1].id == 3){
            map[player.posY][player.posX-1] = Dirt;
        }
        else if(map[player.posY][player.posX+1].id == 3){
            map[player.posY][player.posX+1] = Dirt;
        }
    }
    else{
        printf("Pas d'arbre a casser\n");
    }
}
*/