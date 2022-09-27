# include <stdio.h>
# include <stdlib.h>
# include "map.h"

// Function to create the menu : START
int displayMenu(){
    printf("Welcome to the game !\n");
    printf("Choose your option :\n\n");
    printf("1. Start a new game\n");
    printf("2. Load a game\n");
    printf("3. Exit\n\n");
    
    int choice;
    scanf("%d", &choice);

    if(choice == 1){
        return 1;
    }
    else if(choice == 2){
        return 2;
    }
    else if(choice == 3){
        return 3;
    }
    else return 0;
}
// Function to create the menu : END
void game(){
    Bloc ** map = NULL;
    int value = displayMenu();
    if(value == 1){
        int size;
        printf("Entrez la taille de votre map(cette valeur definira la largeur et la longueur de la map) : ");
        scanf("%d", &size);
        map = generateMap(size);
        displayMap(map, size);
        /*fflush(stdout);
        char c = _getch();
        printf("%c", c);*/
    }
    else if(value == 2){
        //TODO
    }
    else if(value == 3){
    }
}

int main(){
    game();
    return 0;
}