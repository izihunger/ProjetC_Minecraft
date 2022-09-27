#ifndef MAP_H
#define MAP_H

typedef struct Bloc
{
    int id;
    char * display;
    int crossable;
    int spawnable;
    int breakable;
    //Item item;
}Bloc;

const Bloc Dirt;
const Bloc Stone;
const Bloc Tree;
const Bloc Water;

Bloc** createGrid(int size);
Bloc chooseBloc(int r);
Bloc** generateMap(int size);
void displayMap(Bloc ** map, int size);

#endif