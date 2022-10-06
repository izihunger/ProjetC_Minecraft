#pragma once

#include "item.h"
#include "perlin.h"

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
    int chest;
}Bloc;

typedef struct Chest{
    int posX;
    int posY;
    Item items[2];
}Chest;

extern const Bloc Dirt;
extern const Bloc Stone;
extern const Bloc Water;
extern const Bloc Tree;
extern const Bloc Sand;

extern Chest * chest;

Bloc** createGrid(int size);
//Bloc chooseBloc(Bloc ** map, int i, int j, int size);
Bloc chooseBloc(float perlinValue);
Bloc** generateMap(int size);
Bloc ** loadMap(char * filename, char name[20], int * mapsize);
void displayMap(Bloc ** map, int size);
void fillChest(Chest * chest);