#pragma once

#include <time.h>

typedef struct Bloc
{
    int id;
    char * display;
    int crossable;
    int spawnable;
    int breakable;
    int movable;
    int playerOn;
    //Item item;
}Bloc;

Bloc** createGrid(int size);
Bloc chooseBloc(Bloc ** map, int i, int j, int size);
Bloc** generateMap(int size);
Bloc ** loadMap(int size);
void displayMap(Bloc ** map, int size);