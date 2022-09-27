#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "map.h"

const Bloc Dirt = {0, "\033[33md", 1, 1, 1};
const Bloc Stone = {1, "\033[37ms", 1, 1, 1};
const Bloc Tree = {2, "\033[32mt", 0, 1, 0};
const Bloc Water = {3, "\033[34mw", 1, 1, 1};

// Function to generate the map : START
Bloc** createGrid(int size){
    Bloc ** map = (Bloc**) malloc(size * sizeof(Bloc*));
    for (int i = 0; i < size; i++)
    {
        map[i] = (Bloc*) malloc(size * sizeof(Bloc));
    }
    return map;
}

Bloc chooseBloc(int r){
    switch (r)
    {
    case 0:
        return Dirt;
    case 1:
        return Stone;
    case 2:
        return Tree;
    case 3:
        return Water;
    default:
        break;
    }
}

Bloc** generateMap(int size){
    srand(time(NULL));
    Bloc ** map = createGrid(size);
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            int r = rand() % 4;
            map[i][j] = chooseBloc(r);
        }
    }
    return map;
}
// Function to generate the map : END

void displayMap(Bloc ** map, int size){
    //system("cls");
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            printf("%s ", map[i][j].display);
        }
        printf("\n");
    }
}