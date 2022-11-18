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

// Function to use the row mode (catch keyboard without press enter)
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

// Function to load the map from a file
Bloc ** loadMap(char name[20], int * mapsize){
    int size, i = 0, j = 0;
    FILE * file = fopen("./Save.txt", "r");
    char c;
    char siz[255], nam[255], nbmobs[255], nbchests[255], disp[255];
    char *psize = siz, *pname = nam, *pnbmobs = nbmobs, *pnbchests = nbchests, *pdisp = disp;
    while((c=fgetc(file))!=EOF && c != '\n'){
        if(c == ';') j++;
        else{
            if(j == 0) {
                *psize = c;
                psize++;
            }
            else if(j == 1) {
                if(psize != siz){
                    *psize = '\0';
                    size = atoi(siz);
                    *mapsize = size;
                    psize = siz;
                } 
                *pname = c;
                pname++;
            }
            else if(j == 2) {
                if(pname != nam){
                    *pname = '\0';
                    pname = nam;
                    strcpy(name, (char*) nam);
                } 
                *pnbmobs = c;
                pnbmobs++;
            }
            else if(j == 3) {
                if(pnbmobs != nbmobs){
                    *pnbmobs = '\0';
                    pnbmobs = nbmobs;
                    nbMob = atoi(nbmobs);
                } 
                *pnbchests = c;
                pnbchests++;
            }
        }
    }
    *pnbchests = '\0';
    nbChest = atoi(nbchests);
    //réception joueur
    int items = 0;
    j = 0;
    while((c=fgetc(file))!=EOF){
        if(c == ';'){
            j++;
        } 
        else if(j == 8 && c == '\n'){
            *pdisp = '\0';
            pdisp = disp;
            player.nbItems = atoi(disp);
            break;
        }
        else if(j < 9){
            switch (j)
            {
            case 0:
                *pdisp = c;
                pdisp++;
                break;
            case 1:
                if(pdisp != disp){
                    *pdisp = '\0';
                    pdisp = disp;
                    strcpy(player.name, (char*) nam);
                }
                *pname = c;
                pname++;
                break;
            case 2:
                if(pname != nam){
                    *pname = '\0';
                    pname = nam;
                    player.level = atoi(nam);
                }
                *pdisp = c;
                pdisp++;
                break;
            case 3:
                if(pdisp != disp){
                    *pdisp = '\0';
                    pdisp = disp;
                    player.level = atoi(disp);
                }
                *pname = c;
                pname++;
                break;
            case 4:
                if(pname != nam){
                    *pname = '\0';
                    pname = nam;
                    player.hp = atoi(nam);
                }
                *pdisp = c;
                pdisp++;
                break;
            case 5:
                if(pdisp != disp){
                    *pdisp = '\0';
                    pdisp = disp;
                    player.res = atoi(disp);
                }
                *pname = c;
                pname++;
                break;
            case 6:
                if(pname != nam){
                    *pname = '\0';
                    pname = nam;
                    player.atk = atoi(nam);
                }
                *pdisp = c;
                pdisp++;
                break;
            case 7:
                if(pdisp != disp){
                    *pdisp = '\0';
                    pdisp = disp;
                    player.posX = atoi(disp);
                }
                *pname = c;
                pname++;
                break;
            case 8:
                if(pname != nam){
                    *pname = '\0';
                    pname = nam;
                    player.posY = atoi(nam);
                }
                *pdisp = c;
                pdisp++;
                break;
            default:
                break;
            }
        }
        else if(j >= 9 && player.nbItems >= items){
            if(j == 9){
                *pdisp = '\0';
                pdisp = disp;
                player.nbItems = atoi(disp);
            }
            if(j == 8+items){
                if(pdisp != disp){
                    *pdisp = '\0';
                    pdisp = disp;
                    strcpy(player.inventory[items].name,(char*) disp);
                }
                *pname = c;
                pname ++;
            }
            if(j == 8+items+1){
                if(pname != nam){
                    *pname = '\0';
                    pname = nam;
                    player.inventory[items].id = atoi(nam);
                }
                *pdisp = c;
                pdisp ++;
            }
            items ++;
        }
        else break;
    }
    pdisp = disp;
    i = 0;
    j = 0;
    Bloc ** map = createGrid(size);
    Bloc * liste = (Bloc*) malloc(size*size*sizeof(Bloc));
    while(i < size*size && (c=fgetc(file))!=EOF){
        if(c == '\n'){
            i ++;
            j = 0;
            pdisp = disp;
        }
        else if(c == ';') j++;
        else {
            switch (j)
            {
            case 0:
                liste[i].id = c-48;
                break;
            case 1:
                *pdisp = c;
                pdisp++;
                break;
            case 2:
                *pdisp = '\0';
                pdisp = disp;
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
            case 7:
                liste[i].chest = c-48;
                break;
            case 8:
                liste[i].mobOn = c-48;
                break;
            case 9:
                liste[i].vision = c-48;
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
            map[i][j].spawnable = liste[indexe].spawnable;
            map[i][j].crossable = liste[indexe].crossable;
            map[i][j].movable = liste[indexe].movable;
            map[i][j].playerOn = liste[indexe].playerOn;
            map[i][j].chest = liste[indexe].chest;
            map[i][j].mobOn = liste[indexe].mobOn;
            map[i][j].vision = liste[indexe].vision;
            strcpy(map[i][j].display, liste[indexe].display);
            indexe++;
        }
    }
    j = 0;
    i = 0;
    char hp[255], atk[255], posX[255], posY[255];
    char *php = hp, *patk = atk, *pposX = posX, *pposY = posY;
    Mob m;
    mallocMob(nbMob);
    while(i < nbMob && (c=fgetc(file))!=EOF){
        if(c == '\n'){
            *pposY = '\0';
            m.posY = atoi(posY);
            setMob(i, m);
            j = 0;
            pposY = posY;
            i++;
        }
        else if(c == ';') j++;
        else {
            switch (j)
            {
            case 0:
                *pname = c;
                pname++;
                break;
            case 1:
                if(pname != nam){
                    *pname = '\0';
                    pname = nam;
                    strcpy(m.name, (char*) nam);
                }
                *php = c;
                php++;
                break;
            case 2:
                if(php != hp){
                    *php = '\0';
                    php = hp;
                    m.hp = atoi(hp);
                }
                *patk = c;
                patk++;
                break;
            case 3:
                if(patk != atk){
                    *patk = '\0';
                    patk = atk;
                    m.atk = atoi(atk);
                }
                *pposX = c;
                pposX++;
                break;
            case 4:
                if(pposX != posX){
                    *pposX = '\0';
                    pposX = posX;
                    m.posX = atoi(posX);
                }
                *pposY = c;
                pposY++;
                break;
            default:
                break;
            }
        }
    }
    j = 0;
    i = 0;
    char id[255];
    char *pid = id;
    chest = (Chest*) malloc(nbChest * sizeof(Chest));
    Chest tempchest;
    Item it1;
    Item it2;
    while((c=fgetc(file))!=EOF && i < nbChest){
        if(c == '\n'){
            *pname = '\0';
            pname = nam;
            strcpy(it2.name, (char*) nam);
            tempchest.items[0] = it1;
            tempchest.items[1] = it2;
            chest[i] = tempchest;
            j = 0;
            pposY = posY;
            i++;
        }
        else if(c == ';') j++;
        else {
            switch (j)
            {
            case 0:
                *pposX = c;
                pposX++;
                break;
            case 1:
                if(pposX != posX){
                    *pposX = '\0';
                    pposX = posX;
                    tempchest.posX = atoi(posX);
                }
                *pposY = c;
                pposY++;
                break;
            case 2:
                if(pposY != posY){
                    *pposY = '\0';
                    pposY = posY;
                    tempchest.posY = atoi(posY);
                }
                *pid = c;
                pid++;
                break;
            case 3:
                if(pid != id){
                    *pid = '\0';
                    pid = id;
                    it1.id = atoi(id);
                }
                *pname = c;
                pname++;
                break;
            case 4:
                if(pname != nam){
                    *pname = '\0';
                    pname = nam;
                    strcpy(it1.name, (char*) nam);
                }
                *pid = c;
                pid++;
                break;
            case 5:
                if(pid != id){
                    *pid = '\0';
                    pid = id;
                    it2.id = atoi(id);
                }
                *pname = c;
                pname++;
                break;
            default:
                break;
            }
        }
    }
    fclose(file);
    return map;
}

// Function to display the start menu
void displayStartMenu(int *play, gameStatut * game){
    char choice;
    do
    {
        system("clear");
        printf("Welcome to the game !\n");
        printf("Choose your option :\n\n");
        printf("1. Start a new game\n");
        printf("2. Load a game\n");
        printf("3. Exit\n\n");
        
        printf("Enter your choice : ");
        scanf("%c", &choice);

        if(choice == '1'){
            printf("Entrez la taille de votre map(cette valeur definira la largeur et la longueur de la map) : ");
            scanf("%d", &game->size);
            printf("Entrez votre nom de joueur : ");
            scanf("%s", game->playerName);
            strcpy(player.name,(char *) game->playerName);
            game->map = generateMap(game->size);
            spawnPlayer(game->map, game->size);
            int nbSpawnMob = game->size * 15 / 100;
            for(int i = 0; i < nbSpawnMob; i++){
                spawnMob(game->map, game->size);
            }
        }
        else if(choice == '2'){
            game->map = loadMap(game->playerName, &game->size);
            for(int i = 0; i < game->size; i++){
                for(int j = 0; j < game->size; j++){
                    if(game->map[i][j].playerOn == 1) setPos(j, i);
                }
            }
        }
        else if(choice == '3'){
            printf("Le jeu va s'arréter dans 5 secondes...\n");
            sleep(5);
            *play = 0;
        }
    } while (choice != '1' && choice != '2' && choice != '3');
}

// Function to display the in game menu
void displayMenu(gameStatut * game, int * play){
    char choice;
    do
    {
        system("clear");
        printf("Welcome to the menu !\n");
        printf("Choose your option :\n\n");
        printf("1. Return to the game\n");
        printf("2. Save and quit the game\n");
        printf("3. Quit game without saving\n\n");
    
        printf("Enter your choice : ");
        scanf("%c", &choice);
        if(choice == '2'){
            Mob array_mob[nbMob];               // Création d'un tableau de mob qui va contenir les mobs de la map
            for(int i = 0; i < nbMob; i++){     // car les fopen et fprintf modifie les valeurs de mes mobs dans la variable mobs
                array_mob[i] = getMob(i);
            }
            FILE * file = fopen("./Save.txt", "w");
            fprintf(file, "%d;%s;%d;%d\n", game->size, game->playerName, nbMob, nbChest);
            fprintf(file, "%s;%d;%d;%d;%d;%d;%d;%d;%d", player.name, player.xp, player.level, player.hp, player.res, player.atk, player.posX, player.posY, player.nbItems);
            if(player.nbItems){
                for(int i = 0; i < player.nbItems; i++){
                    fprintf(file, ";%d;%s", player.inventory[i].id, player.inventory[i].name);
                }
            }
            fprintf(file, "\n");
            for(int i = 0; i < game->size; i++){
                for(int j = 0; j < game->size; j++){
                    fprintf(file, "%d;%s;%d;%d;%d;%d;%d;%d;%d;%d\n", game->map[i][j].id, game->map[i][j].display, game->map[i][j].crossable,\
                                                                    game->map[i][j].spawnable, game->map[i][j].breakable, game->map[i][j].movable,\
                                                                    game->map[i][j].playerOn, game->map[i][j].chest, game->map[i][j].mobOn,\
                                                                    game->map[i][j].vision);
                }
            }
            for(int i = 0; i < nbMob; i++){
                fprintf(file, "%s;%d;%d;%d;%d\n", array_mob[i].name, array_mob[i].hp, array_mob[i].atk, array_mob[i].posX, array_mob[i].posY);
            }
            for(int i = 0; i < nbChest; i++){
                fprintf(file, "%d;%d;%d;%s;%d;%s\n", chest[i].posX, chest[i].posY, chest[i].items[0].id, chest[i].items[0].name,\
                                                    chest[i].items[1].id, chest[i].items[1].name);
            }
            fclose(file);
            *play = 0;
            printf("Le jeu va s'arréter dans 5 secondes...\n");
            sleep(5);
        }
        else if(choice == '3'){
            *play = 0;
            printf("Le jeu va s'arréter dans 5 secondes...\n");
            sleep(5);
        }
    } while (choice != '1' && choice != '2' && choice != '3' && choice != '4');
}

// Function to run the game
void game(){
    srand(time(NULL));
    gameStatut game;
    int play = 1;
    displayStartMenu(&play, &game);
    mode_raw(1);
    char c;
    while(play){
        c = getchar();
        if(c == 'm') {
            mode_raw(0);
            displayMenu(&game, &play);
            mode_raw(1);
        }
        else if(c == 'i'){
            mode_raw(0);
            displayInventory();
            mode_raw(1);
        }
        else if(c == 'r'){
            mode_raw(0);
            manger();
            mode_raw(1);
            moveMob(game.map, game.size);
            displayMap(game.map, game.size);
            mode_raw(0); 
            if(!fight(game.map, game.size)){
                play = 0;
            }
            mode_raw(1); 
        }
        else if(c == 'z' || c == 'q' || c == 's' || c == 'd' || c == 't'){
            movePlayer(game.map,game.size, c);
            if(game.map[player.posY][player.posX].chest){
                mode_raw(0);               
                openChest(game.map);
                mode_raw(1);
            }
            moveMob(game.map, game.size);
            displayMap(game.map, game.size);
            mode_raw(0); 
            if(!fight(game.map, game.size)){
                play = 0;
            }
            mode_raw(1); 
        }
        if(player.hp > 0){
            displayMap(game.map, game.size);
            displayPlayerXP();
            displayCommand(player.hp);
        }
    }
    mode_raw(0);
    for (int i = 0; i < game.size; i++)
        free(game.map[i]);
    free(game.map);
    free(chest);
}

int main(){
    game();
    return 0;
}