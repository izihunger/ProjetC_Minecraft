#pragma once

#include <time.h>
#include <string.h>

typedef struct Bloc
{
    int id;
    char display[255];
    int crossable;
    int spawnable;
    int breakable;
    int movable;
    int playerOn;
    int mobOn;
    //Item item;
}Bloc;

Bloc** createGrid(int size);
Bloc chooseBloc(Bloc ** map, int i, int j, int size);
Bloc** generateMap(int size);
Bloc ** loadMap(char * filename, char name[20], int * mapsize);
void displayMap(Bloc ** map, int size);