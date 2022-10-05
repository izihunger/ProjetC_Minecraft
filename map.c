#include <stdio.h>
#include <stdlib.h>
#include "map.h"

const Bloc Dirt = {0, "\033[31m#", 1, 1, 0, 0, 0, 0};
const Bloc Stone = {1, "\033[37m#", 1, 1, 0, 0, 0, 0};
const Bloc Water = {2, "\033[34m~", 0, 0, 0, 0, 0, 0};
const Bloc Tree = {3, "\033[32mT", 0, 0, 1, 0, 0, 0};

Chest * chest;

// Function to generate the map : START
Bloc** createGrid(int size){
    Bloc ** map = (Bloc**) malloc(size * sizeof(Bloc*));
    for (int i = 0; i < size; i++)
    {
        map[i] = (Bloc*) malloc(size * sizeof(Bloc));
    }
    return map;
}

Bloc chooseBloc(Bloc ** map, int i, int j, int size){
    int r;
    if(j == 0)
        r = rand() % 4;
    else if(map[i][j-1].id == 0){
        //printf("Last is dirt\n");
        r = rand() % 100;
        //printf("Pourcentage : %d\n", r);
        if(r >= 0 && r < 40) r = 0;
        else if(r >= 40 && r < 65) r = 1;
        else if(r >= 65 && r < 90) r = 2;
        else r = 3;
    }
    else if(map[i][j-1].id == 1){
        //printf("Last is stone\n");
        r = rand() % 100;
        //printf("Pourcentage : %d\n", r);
        if(r >= 0 && r < 40) r = 0;
        else r = 1;
    }
    else if(map[i][j-1].id == 2){
        //printf("Last is water\n");
        r = rand() % 100;
        //printf("Pourcentage : %d\n", r);
        if(r >= 0 && r < 35) r = 0;
        else r = 2;
    }
    else if(map[i][j-1].id == 3){
        //printf("Last is tree\n");
        r = rand() % 100;
        //printf("Pourcentage : %d\n", r);
        if(r >= 0 && r < 70) r = 0;
        else r = 3;
    }
    //printf("%d\n", r);
    switch (r)
    {
    case 0:
        return Dirt;
    case 1:
        return Stone;
    case 2:
        return Water;
    case 3:
        return Tree;
    default:
        return Dirt;
    }
}

Bloc** generateMap(int size){
    Bloc ** map = createGrid(size);
    int nbCoffres = 0;
    srand(time(NULL));
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            map[i][j] = chooseBloc(map, i, j, size);
            if(map[i][j].id == 0){
                int r = rand() % 100;
                if(r <= 2){
                    map[i][j].chest = 1;
                    nbCoffres ++;
                }
            }
        }
    }
    chest = (Chest*) malloc(nbCoffres * sizeof(Chest));
    int k = 0;
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(map[i][j].chest){
                chest[k].posX = j;
                chest[k].posX = i;
            }
        }
    }
    return map;
}
// Function to generate the map : END

Bloc ** loadMap(char * filename, char name[20], int * mapsize){
    int size, i = 0, j = 0;
    FILE * file = fopen(filename, "r");
    char c;
    char siz[255], nam[255], disp[255];
    char *s = siz;
    char *p = nam;
    while((c=fgetc(file))!=EOF && c != '\n'){
        if(c == ';') j++;
        else{
            if(j == 0) {
                *s = c;
                s++;
            }
            if(j == 1) {
                if(s != siz) *s = '\0';
                s = siz;
                *p = c;
                p++;
            }
        }
    }
    size = atoi(siz);
    *mapsize = size;
    *p = '\0';
    s = disp;
    j = 0;
    strcpy(name, (char*) nam);
    Bloc ** map = createGrid(size);
    Bloc * liste = (Bloc*) malloc(size*size*sizeof(Bloc));
    while((c=fgetc(file))!=EOF){
        if(c == '\n'){
            i ++;
            j = 0;
            s = disp;
        }
        else if(c == ';') j++;
        else {
            switch (j)
            {
            case 0:
                liste[i].id = c-48;
                break;
            case 1:
                *s = c;
                s++;
                break;
            case 2:
                *s = '\0';
                s = disp;
                strcpy(liste[i].display, (char*) disp);
                liste[i].crossable = c-48; 
                break;
            case 3:
                liste[i].spawnable = c-48;
                break;
            case 4:
                liste[i].breakable = c-48;
                break;
            case 5:
                liste[i].movable = c-48;
                break;
            case 6:
                liste[i].playerOn = c-48;
                break;
            default:
                break;
            }
        }
    }
    int indexe = 0;
    for(i = 0; i < size; i++){
        for(j = 0; j < size; j++){
            map[i][j].id = liste[indexe].id;
            map[i][j].breakable = liste[indexe].breakable;
            map[i][j].crossable = liste[indexe].crossable;
            map[i][j].movable = liste[indexe].movable;
            map[i][j].playerOn = liste[indexe].playerOn;
            strcpy(map[i][j].display, liste[indexe].display);
            indexe++;
        }
    }
    fclose(file);
    return map;
}

void displayMap(Bloc ** map, int size){
    system("clear");
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(map[i][j].playerOn) printf("\033[33mP ");
            else if(map[i][j].mobOn) printf("\033[33mM ");
            else if(map[i][j].chest) printf("\033[33m@ ");
            else printf("%s ", map[i][j].display);
        }
        printf("\n");
    }
    printf("\nCommandes :\n\
            \'z\' pour monter\n\
            \'s\' pour descendre\n\
            \'q\' pour aller a gauche\n\
            \'d\' pour aller a gauche\n\
            \'m\' pour entrez dans le menu\n\
            \'e\' pour exit le jeu\n\
            \nEntrez votre commande : ");
}