#include <stdio.h>
#include <stdlib.h>

typedef struct Bloc
{
    char display;
    int crossable;
    int drop;
}Bloc;

void generateMap(Bloc ** map){
    for(int i = 0; i < 5; i++){
        for(int j = 0; i < 5; i++){
            map[i][j].display = 'd';
        }
    }
}

void afficherMap(Bloc ** map){
    for(int i = 0; i < sizeof(map); i++){
        for(int j = 0; i < 5; i++){
            printf("%c", map[i][j].display);
        }
    }
}

int main(){
    Bloc ** map = NULL;
    map = (Bloc**) malloc(5 * sizeof(Bloc*));
    for (int i = 0; i < 5; i++)
    {
        map[i] = (Bloc*) malloc(5 * sizeof(Bloc));
    }
    generateMap(map);
    afficherMap(map);
    return 0;
}