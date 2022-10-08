# include "mob.h"

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
        printf("Enter the path where you want to save : ");
        char path[255];
        scanf("%s", path);
        int len = strlen(path);
        char * txt = "save.txt";
        for(int i = 0; i < strlen(txt); i++){
            path[len+i] = txt[i];
        }
        printf("%s", path);
        FILE * file = fopen("Save.txt", "w");
        fprintf(file, "%d;%s\n", game.size, game.playerName);
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
        spawnMob(game.map, game.size);
        /*fflush(stdout);
        char c = _getch();
        printf("%c", c);*/
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
    displayMap(game.map, game.size);
    displayCommand();
    char c;
    while(scanf(" %c", &c) == 1 && c != 'e'){
        if(c == 'm') displayMenu(game);
        else if(c == 'i'){
            displayInventory();
            displayCommand();
        }
        else if(c == 'z' || c == 'q' || c == 's' || c == 'd' || c == 't'){
            movePlayer(game.map, c);
            moveMob(game.map, getPlayer(), game.size);
            displayMap(game.map, game.size);
            if(game.map[getPlayer().posY][getPlayer().posX].chest){
                int chestChoice;
                printf("Vous etes sur un coffre ! Voulez vous l'ouvrir ? (1 pour oui / 0 pour non) : ");
                if(scanf("%d", &chestChoice)){
                    if(chestChoice){
                        openChest(game.map);
                    }
                }
            } 
            displayCommand();
        }
    }
    free(game.map);
}

int main(){
    game();
    return 0;
}