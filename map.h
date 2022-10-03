#pragma once

#include <time.h>

typedef struct Bloc
{
    int id;
    char * display;
    int crossable;
    int spawnable;
    int breakable;
    int playerOn;
    //Item item;
}Bloc;

Bloc** createGrid(int size);
Bloc chooseBloc(Bloc ** map, int i, int j, int size);
Bloc** generateMap(int size);
void displayMap(Bloc ** map, int size);