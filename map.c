#include <stdio.h>
#include <stdlib.h>
#include "map.h"

const Bloc Dirt = {0, "\033[31m#", 1, 1, 0, 0, 0};
const Bloc Stone = {1, "\033[37m#", 1, 1, 0, 0, 0};
const Bloc Water = {2, "\033[34m~", 0, 0, 0, 0, 0};
const Bloc Tree = {3, "\033[32mT", 0, 0, 1, 0, 0};

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
    if(i == 0 && j == 0)
        r = rand() % 4;
    else if(map[i][j-1].id == 0){
        printf("Last is dirt\n");
        r = rand() % 100;
        printf("Pourcentage : %d\n", r);
        if(r >= 0 && r < 40) r = 0;
        else if(r >= 40 && r < 65) r = 1;
        else if(r >= 65 && r < 90) r = 2;
        else r = 3;
    }
    else if(map[i][j-1].id == 1){
        printf("Last is stone\n");
        r = rand() % 100;
        printf("Pourcentage : %d\n", r);
        if(r >= 0 && r < 40) r = 0;
        else r = 1;
    }
    else if(map[i][j-1].id == 2){
        printf("Last is water\n");
        r = rand() % 100;
        printf("Pourcentage : %d\n", r);
        if(r >= 0 && r < 35) r = 0;
        else r = 2;
    }
    else if(map[i][j-1].id == 3){
        printf("Last is tree\n");
        r = rand() % 100;
        printf("Pourcentage : %d\n", r);
        if(r >= 0 && r < 70) r = 0;
        else r = 3;
    }
    printf("%d\n", r);
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
    srand(time(NULL));
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            map[i][j] = chooseBloc(map, i, j, size);
        }
    }
    return map;
}
// Function to generate the map : END

Bloc ** loadMap(int size){
    int i = 0, j = 0;
    Bloc ** map = createGrid(size);
    Bloc * liste = (Bloc*) malloc(size*size*sizeof(Bloc));
    FILE * file = fopen("Save.txt", "r");
    char c;
    while((c=fgetc(file))!=EOF){
        if(c == '\n'){
            i ++;
            j = 0;
        }
        if(c == ';') j++;
        else {
            char * disp;
            switch (j)
            {
            case 0:
                liste[i].id = (int)c;
                break;
            case 1:
                disp += c;
                break;
            case 2:
                liste[i].display = disp;
                disp = "";
                liste[i].crossable = (int)c;
                break;
            case 3:
                liste[i].spawnable = (int)c;
                break;
            case 4:
                liste[i].breakable = (int)c;
                break;
            case 5:
                liste[i].movable = (int)c;
                break;
            case 6:
                liste[i].playerOn = (int)c;
                break;
            default:
                break;
            }
            printf("%c",c); 
        }
    }
    for(i = 0; i < size*size; i++){
        printf("%s", liste[i].display);
    }
    /*for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            map[i][j] = Dirt;
            //map[i][j] = chooseBloc(map, i, j, size);
        }
    }*/
    fclose(file);
    return map;
}

void displayMap(Bloc ** map, int size){
    system("cls");
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(map[i][j].playerOn) printf("\033[33mP ");
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