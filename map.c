#include <stdio.h>
#include <stdlib.h>
#include "map.h"

// All the blocs to create the map
const Bloc Dirt = {0, "\033[31m# \033[37m", 1, 1, 0, 0, 0, 0, 0, 0};
const Bloc Stone = {1, "\033[37m# \033[37m", 1, 1, 0, 0, 0, 0, 0, 0};
const Bloc Water = {2, "\033[34m~ \033[37m", 0, 0, 0, 0, 0, 0, 0, 0};
const Bloc Tree = {3, "\033[32mT \033[37m", 0, 0, 1, 0, 0, 0, 0, 0};
const Bloc Sand = {4, "\033[33ms \033[37m", 1, 1, 0, 0, 0, 0, 0, 0};

Chest * chest; // Contains all the chest on the map
int nbChest; // Number of chests
char * displayPlayer = "\033[36mᐃ \033[37m"; // Player's display

// Function to generate the grid of map
Bloc** createGrid(int size){
    Bloc ** map = (Bloc**) malloc(size * sizeof(Bloc*));
    for (int i = 0; i < size; i++)
    {
        map[i] = (Bloc*) malloc(size * sizeof(Bloc));
    }
    return map;
}

// Function to choose the bloc with perlin noise
Bloc chooseBloc(float perlinValue){
    if(perlinValue > 0 && perlinValue <= 0.30) return Stone;
    else if(perlinValue > 0.30 && perlinValue <= 0.45) return Dirt;
    else if(perlinValue > 0.50 && perlinValue <= 0.55) return Tree;
    else if(perlinValue > 0.60 && perlinValue <= 0.66) return Sand;
    else if(perlinValue > 0.66 && perlinValue <= 1) return Water;
    else return Dirt;
}

// Function to generate all the map
Bloc** generateMap(int size){
    Bloc ** map = createGrid(size);
    SEED = rand()%10000;
    float perlinValue;
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            perlinValue = perlin2d(j, i, 0.1, 4);
            map[i][j] = chooseBloc(perlinValue);
            if(map[i][j].id == 0){
                int r = rand() % 100;
                if(r <= 2){
                    map[i][j].chest = 1;
                    nbChest ++;
                }
            }
        }
    }
    chest = (Chest*) malloc(nbChest * sizeof(Chest));
    int k = 0;
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(map[i][j].chest){
                chest[k].posX = j;
                chest[k].posY = i;
                fillChest(&chest[k]);
                k++;
            }
        }
    }
    for(int i = 0; i < nbChest; i++){
        for(int j = 0; j < 2; j++){
            printf("%s ", chest[i].items[j].name);
        }
        printf("\n");
    }
    return map;
}

// Function to load the map from a file
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

// Function to display the map with blocs / player / chests / mobs
void displayMap(Bloc ** map, int size){
    system("clear");
    printf("-");
    for(int i = 0; i < size+1; i++) printf("--");
    printf("\r\n");
    for(int i = 0; i < size; i++){
        printf("| ");
        for(int j = 0; j < size; j++){
            if(map[i][j].playerOn) printf("%s", displayPlayer);
            else if(map[i][j].vision){
                if(map[i][j].mobOn) printf("\033[36mM \033[37m");
                else if(map[i][j].chest) printf("\033[35m@ \033[37m");
                else printf("%s", map[i][j].display);
            }
            else printf("  ");
        }
        printf("|\r\n");
    }
    printf("-");
    for(int i = 0; i < size+1; i++) printf("--");
    printf("\r\n");
}

// Function to display the command
void displayCommand(){
    printf("\r\nCommandes :\r\n\
            \'z\' pour monter\r\n\
            \'s\' pour descendre\r\n\
            \'q\' pour aller a gauche\r\n\
            \'d\' pour aller a gauche\r\n\
            \'i\' pour voir votre inventaire\r\n\
            \'t\' pour casser un arbre\r\n\
            \'m\' pour entrez dans le menu\r\n\
            \'e\' pour exit le jeu\r\n\
            \r\nEntrez votre commande : \r");
}

// Function to fill the chests with items
void fillChest(Chest * chest){
    int r1 = rand() % nbItems;
    chest->items[0] = selectItem(r1);
    int r2;
    do{
        r2 = rand() % nbItems;
    }while(r2 == r1);
    chest->items[1] = selectItem(r2);
}