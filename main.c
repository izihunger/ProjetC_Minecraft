#include <stdio.h>
#include <stdlib.h>
#include <conio.h>


// Structure for the linked list : START
typedef struct Bloc
{
    char display;
    int crossable;
    int drop;
    int spawnable;
}Bloc;
// Structure for the linked list : END

// Function to generate the map : START
Bloc** createGrid(int size){
    Bloc ** map = (Bloc**) malloc(size * sizeof(Bloc*));
    for (int i = 0; i < size; i++)
    {
        map[i] = (Bloc*) malloc(size * sizeof(Bloc));
    }
    return map;
}

Bloc** generateMap(int size){
    Bloc ** map = createGrid(size);
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            map[i][j].display = 'd';
        }
    }
    return map;
}
// Function to generate the map : END

void showMap(Bloc ** map, int size){
    system("cls");
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            printf("%c ", map[i][j].display);
        }
        printf("\n");
    }
}

int main(){
    int size;
    printf("Entrez la taille de votre map(cette valeur definira la largeur et la longueur de la map) : ");
    scanf("%d", &size);
    Bloc ** map = generateMap(size);
    showMap(map, size);
    /*fflush(stdout);
    char c = _getch();
    printf("%c", c);*/
    return 0;
}