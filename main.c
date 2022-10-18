# include "mob.h"
#include <termios.h> 
#include <unistd.h> 

typedef struct gameStatut
{
    Bloc ** map;
    int size;
    int difficulty;
    char playerName[20];
}gameStatut;

void mode_raw(int activer) 
{ 
    static struct termios cooked; 
    static int raw_actif = 0; 
  
    if (raw_actif == activer) 
        return; 
  
    if (activer) 
    { 
        struct termios raw; 
  
        tcgetattr(STDIN_FILENO, &cooked); 
  
        raw = cooked; 
        cfmakeraw(&raw); 
        tcsetattr(STDIN_FILENO, TCSANOW, &raw); 
    } 
    else 
        tcsetattr(STDIN_FILENO, TCSANOW, &cooked); 
  
    raw_actif = activer; 
}

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
    system("clear");
    printf("Welcome to the menu !\n");
    printf("Choose your option :\n\n");
    printf("1. Save\n");
    printf("2. Change difficulty\n");
    printf("3. Exit\n\n");
    int choice;
    scanf("%d", &choice);
    if(choice == 1){
        Mob array_mob[nbMob];               // Création d'un tableau de mob qui va contenir les mobs de la map
        for(int i = 0; i < nbMob; i++){     // car les fopen et fprintf modifie les valeurs de mes mobs dans la variable mobs
            array_mob[i] = getMob(i);
        }
        FILE * file = fopen("./Save.txt", "w");
        fprintf(file, "%d;%s;%d\n", game.size, game.playerName, nbMob);
        for(int i = 0; i < nbMob; i++){
            fprintf(file, "%d;%d;%s;%d;%d\n", array_mob[i].atk, array_mob[i].hp, array_mob[i].name, array_mob[i].posX, array_mob[i].posY);
        }
        for(int i = 0; i < game.size; i++){
            for(int j = 0; j < game.size; j++){
                fprintf(file, "%d;%s;%d;%d;%d;%d;%d\n", game.map[i][j].id, game.map[i][j].display, game.map[i][j].crossable,\
                game.map[i][j].spawnable, game.map[i][j].breakable, game.map[i][j].movable, game.map[i][j].playerOn);
            }
        }
        fclose(file);
        for(int i = 0; i < nbMob; i++){     // On remet les mobs dans la variable mobs
            setMob(i, array_mob[i]);
        }
    }
}

// Function to create the start menu : END
void game(){
    srand(time(NULL));
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
        int nbSpawnMob = game.size * 15 / 100;
        for(int i = 0; i < nbSpawnMob; i++){
            spawnMob(game.map, game.size);
        }
    }
    else if(value == 2){
        game.map = loadMap("Save.txt", game.playerName, &game.size);
        for(int i = 0; i < game.size; i++){
            for(int j = 0; j < game.size; j++){
                if(game.map[i][j].playerOn == 1) setPos(j, i);
            }
        }
    }
    else if(value == 3){
    }
    mode_raw(1);
    int play = 1;
    char c;
    while(play){
        displayMap(game.map, game.size);
        displayCommand();
        c = getchar();
        if(c == 'e') play = 0;
        else if(c == 'm') {
            mode_raw(0);
            displayMenu(game);
            mode_raw(1);
        }
        else if(c == 'i'){
            mode_raw(0);
            displayInventory();
            mode_raw(1);
        }
        else if(c == 'z' || c == 'q' || c == 's' || c == 'd' || c == 't'){
            movePlayer(game.map,game.size, c);
            if(game.map[getPlayer().posY][getPlayer().posX].chest){
                mode_raw(0);
                openChest(game.map);
                mode_raw(1);
            } 
        }
        moveMob(game.map, getPlayer(), game.size);
    }
    mode_raw(0);
    free(game.map);
}

int main(){
    game();
    return 0;
}