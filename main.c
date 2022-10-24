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
        FILE * file = fopen("../Save.txt", "w");
        fprintf(file, "%d;%s;%d;%d\n", game.size, game.playerName, nbMob, nbChest);
        for(int i = 0; i < game.size; i++){
            for(int j = 0; j < game.size; j++){
                fprintf(file, "%d;%s;%d;%d;%d;%d;%d;%d;%d;%d\n", game.map[i][j].id, game.map[i][j].display, game.map[i][j].crossable,\
                                                                game.map[i][j].spawnable, game.map[i][j].breakable, game.map[i][j].movable,\
                                                                game.map[i][j].playerOn, game.map[i][j].chest, game.map[i][j].mobOn,\
                                                                game.map[i][j].vision);
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
        for(int i = 0; i < nbMob; i++){     // On remet les mobs dans la variable mobs
            setMob(i, array_mob[i]);
        }
    }
}

// Function to load the map from a file
Bloc ** loadMap(char name[20], int * mapsize){
    int size, i = 0, j = 0;
    FILE * file = fopen("../Save.txt", "r");
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
            printf("%s, %d, %d, %d, %d\r\n", m.name, m.hp, m.atk, m.posX, m.posY);
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
    while((c=fgetc(file))!=EOF){
        if(c == '\n'){
            *pname = '\0';
            pname = nam;
            strcpy(it2.name, (char*) nam);
            tempchest.items[0] = it1;
            tempchest.items[1] = it2;
            chest[i] = tempchest;
            printf("%d, %s\n", chest[i].items[1].id, chest[i].items[1].name);
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

// Function to create the start menu : END
void game(){
    srand(time(NULL));
    gameStatut game;
    int play = 1;
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
        game.map = loadMap(game.playerName, &game.size);
        printf("%d\n", game.size);
        for(int i = 0; i < game.size; i++){
            for(int j = 0; j < game.size; j++){
                if(game.map[i][j].playerOn == 1) setPos(j, i);
            }
        }
    }
    else if(value == 3){
        printf("Le jeu va s'arréter dans 5 secondes...\n");
        sleep(5);
        play = 0;
    }
    mode_raw(1);
    char c;
    while(play){
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
        else if(c == 'r'){
            mode_raw(0);
            manger();
            mode_raw(1);
        }
        else if(c == 'z' || c == 'q' || c == 's' || c == 'd' || c == 't'){
            movePlayer(game.map,game.size, c);
            if(game.map[player.posY][player.posX].chest){
                mode_raw(0);               
                openChest(game.map);
                mode_raw(1);
            }
        }
        moveMob(game.map, game.size);
        displayMap(game.map, game.size);
        mode_raw(0); 
        if(!fight(game.map, game.size)){
            play = 0;
        }
        mode_raw(1); 
        displayMap(game.map, game.size);
        displayCommand(player.hp);
    }
    mode_raw(0);
    free(game.map);
}

int main(){
    game();
    return 0;
}