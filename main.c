# include <stdio.h>
# include <stdlib.h>
# include "player.h"

typedef struct gameStatut
{
    Bloc ** map;
    int size;
    int difficulty;
    char playerName[20];
}gameStatut;


// Function to create the start menu : START
int displayStartMenu(){
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

void displayMenu(gameStatut game){
    system("cls");
    printf("Welcome to the menu !\n");
    printf("Choose your option :\n\n");
    printf("1. Save\n");
    printf("2. Change difficulty\n");
    printf("3. Exit\n\n");
    int choice;
    scanf("%d", &choice);
    if(choice == 1){
        FILE * file = fopen("Save.txt", "w");
        //fprintf(file, "%d\n", game.size);
        for(int i = 0; i < game.size; i++){
            for(int j = 0; j < game.size; j++){
                fprintf(file, "%d;%s;%d;%d;%d;%d;%d\n", game.map[i][j].id, game.map[i][j].display, game.map[i][j].crossable,\
                game.map[i][j].spawnable, game.map[i][j].breakable, game.map[i][j].movable, game.map[i][j].playerOn);
            }
        }
        fclose(file);
    }
}
// Function to create the start menu : END
void game(){
    gameStatut game;
    int value = displayStartMenu();
    if(value == 1){
        printf("Entrez la taille de votre map(cette valeur definira la largeur et la longueur de la map) : ");
        scanf("%d", &game.size);
        printf("Entrez votre nom de joueur : ");
        scanf("%s", game.playerName);
        setPlayerName(game.playerName);
        game.map = generateMap(game.size);
        spawnPlayer(game.map, game.size);
        /*fflush(stdout);
        char c = _getch();
        printf("%c", c);*/
    }
    else if(value == 2){
        game.size = 20;
        game.map = loadMap(game.size);
        for(int i = 0; i < game.size; i++){
            for(int j = 0; j < game.size; j++){
                if(game.map[i][j].playerOn == 1) setPos(j, i);
            }
        }
    }
    else if(value == 3){
    }
    displayMap(game.map, game.size);
    char c;
    while(scanf(" %c", &c) == 1 && c != 'e'){
        if(c == 'm') displayMenu(game);
        else{
            movePlayer(game.map, c);
            displayMap(game.map, game.size);
        }
    }
    free(game.map);
}

int main(){
    game();
    return 0;
}