# include <stdio.h>
# include <stdlib.h>
# include "player.h"

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
    int size;
    int value = displayMenu();
    if(value == 1){
        printf("Entrez la taille de votre map(cette valeur definira la largeur et la longueur de la map) : ");
        scanf("%d", &size);
        map = generateMap(size);
        /*fflush(stdout);
        char c = _getch();
        printf("%c", c);*/
    }
    else if(value == 2){
        //TODO
    }
    else if(value == 3){
    }
    spawPlayer(map, size);
    displayMap(map, size);
    char c;
    while(scanf(" %c", &c) == 1){
        movePlayer(map, c);
        displayMap(map, size);
    }
    free(map);
}

int main(){
    printf("Hello there: \U0001F600\n");
    game();
    return 0;
}