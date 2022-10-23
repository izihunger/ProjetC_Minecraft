#include "mob.h"

Mob mob = {"zombie", 20, 8, 0, 0};

Mob * mobs;
int nbMob = 0;

// Fonction pour faire spawn un mob
void spawnMob(Bloc ** map, int size){
    printf("Debut spawn mob\n");
    int i,j;
    do{
        printf("Boucle position\n");
        i = rand() % size;
        j = rand() % size;
        printf("%d, %d, %d, %d\n", map[i][j].spawnable, map[i][j].playerOn, map[i][j].mobOn, map[i][j].chest);
    }while(!map[i][j].spawnable || map[i][j].chest || map[i][j].playerOn || map[i][j].mobOn); // On vérifie que le bloc est spawnable et qu'il n'y a pas de coffre
    printf("Position trouve\n");
    if(nbMob == 0){
        mobs = (Mob*) malloc(sizeof(Mob));
    } 
    else {
        mobs = (Mob*) realloc(mobs, nbMob+1 * sizeof(Mob));
    }
    mobs[nbMob] = mob;
    mobs[nbMob].posX = j;
    mobs[nbMob].posY = i;
    nbMob++;
    map[i][j].mobOn = 1; // On met le mob sur la map
    printf("Fin spawn mob\n");
}

// Fonction pour faire bouger le mob
void moveMob(Bloc ** map, Player player, int size){
    printf("oui\r\n");
    for(int i = 0; i<nbMob; i++){
        int move = rand() % 4; // On génère un nombre entre 0 et 3 pour déterminer si le mob bouge ou pas
        if(move != 0){
            if(abs(mobs[i].posX - player.posX) < 20 && abs(mobs[i].posY - player.posY) < 20){ // Si le joueur est à moins de 20 blocs du mob (agro du joueur)
                printf("J-20\r\n");
                if(abs(player.posX - mobs[i].posX) > abs(player.posY - mobs[i].posY)){ // Si la distance entre le joueur et le mob est plus grande en x que en y (le mob se déplace en x)
                    printf("X\r\n");
                    if(player.posX > mobs[i].posX){
                        printf("player > mob\r\n");
                        if(mobs[i].posX+1 < size){
                            printf("non\r\n");
                            if(map[mobs[i].posY][mobs[i].posX + 1].crossable && !map[mobs[i].posY][mobs[i].posX + 1].playerOn && !map[mobs[i].posY][mobs[i].posX + 1].mobOn){ // Si le bloc à droite du mob est crossable (déplacement vers la droite)
                                printf("oui\r\n");
                                map[mobs[i].posY][mobs[i].posX].mobOn = 0;
                                mobs[i].posX ++;
                                map[mobs[i].posY][mobs[i].posX].mobOn = 1;
                            }
                        }
                    }
                    else{
                        printf("player < mob\r\n");
                        if(mobs[i].posX-1 >= 0){
                        printf("non\r\n");
                            if(map[mobs[i].posY][mobs[i].posX - 1].crossable && !map[mobs[i].posY][mobs[i].posX - 1].playerOn && !map[mobs[i].posY][mobs[i].posX - 1].mobOn){ // Si le bloc à gauche du mob est crossable (déplacement vers la gauche)
                                printf("oui\r\n");
                                map[mobs[i].posY][mobs[i].posX].mobOn = 0;
                                mobs[i].posX --;
                                map[mobs[i].posY][mobs[i].posX].mobOn = 1;
                            }
                        }
                    }
                }
                else{ // Si la distance entre le joueur et le mob est plus grande en y que en x (le mob se déplace en y)
                    printf("Y\r\n");
                    if(player.posY > mobs[i].posY){
                        if(mobs[i].posY+1 < size){
                            if(map[mobs[i].posY + 1][mobs[i].posX].crossable && !map[mobs[i].posY + 1][mobs[i].posX].playerOn && !map[mobs[i].posY + 1][mobs[i].posX].mobOn){ // Si le bloc en dessous du mob est crossable (déplacement vers le bas)
                                map[mobs[i].posY][mobs[i].posX].mobOn = 0;
                                mobs[i].posY ++;
                                map[mobs[i].posY][mobs[i].posX].mobOn = 1;
                            }
                        }
                    }
                    else{
                        if(mobs[i].posY-1 >= 0){
                            if(map[mobs[i].posY - 1][mobs[i].posX].crossable && !map[mobs[i].posY - 1][mobs[i].posX].playerOn && !map[mobs[i].posY - 1][mobs[i].posX].mobOn){ // Si le bloc au dessus du mob est crossable (déplacement vers le haut)
                                map[mobs[i].posY][mobs[i].posX].mobOn = 0;
                                mobs[i].posY --;
                                map[mobs[i].posY][mobs[i].posX].mobOn = 1;
                            }
                        }
                    }
                }
            }
            else{ // Si le joueur est à plus de 20 blocs du mob (déplacement aléatoire du mob)
                int a = rand() % 4; // Choix aléatoire de la direction du mob
                switch (a)
                {
                case 0: // Déplacement vers le haut
                    if(mobs[i].posY-1 >= 0){
                        if(map[mobs[i].posY - 1][mobs[i].posX].crossable && !map[mobs[i].posY - 1][mobs[i].posX].mobOn){
                            map[mobs[i].posY][mobs[i].posX].mobOn = 0;
                            mobs[i].posY --;
                            map[mobs[i].posY][mobs[i].posX].mobOn = 1;
                        }
                    }
                    break;
                case 1: // Déplacement vers le bas
                    if(mobs[i].posY+1 < size){
                        if(map[mobs[i].posY + 1][mobs[i].posX].crossable && !map[mobs[i].posY + 1][mobs[i].posX].mobOn){
                            map[mobs[i].posY][mobs[i].posX].mobOn = 0;
                            mobs[i].posY ++;
                            map[mobs[i].posY][mobs[i].posX].mobOn = 1;
                        }
                    }
                    break;
                case 2: // Déplacement vers la gauche
                    if(mobs[i].posX-1 >= 0){
                        if(map[mobs[i].posY][mobs[i].posX - 1].crossable && !map[mobs[i].posY][mobs[i].posX - 1].mobOn){
                            map[mobs[i].posY][mobs[i].posX].mobOn = 0;
                            mobs[i].posX --;
                            map[mobs[i].posY][mobs[i].posX].mobOn = 1;
                        }
                    }
                    break;
                case 3: // Déplacement vers la droite
                    if(mobs[i].posX+1 < size){
                        if(map[mobs[i].posY][mobs[i].posX + 1].crossable && !map[mobs[i].posY][mobs[i].posX + 1].mobOn){
                            map[mobs[i].posY][mobs[i].posX].mobOn = 0;
                            mobs[i].posX ++;
                            map[mobs[i].posY][mobs[i].posX].mobOn = 1;
                        }
                    }
                    break;
                default:
                    break;
                }
            }
        }
    }
}

void fight(Bloc ** map, Player player, char c){
    srand(time(NULL));
    int critique = rand() % 5;
    int esquive = rand() % 4;

    for(int i = 0; i<nbMob; i++){
        if(map[mobs[i].posY + 1][mobs[i].posX].playerOn){ // Le mob est 1 case au dessus du joueur
        printf("%d vie mob \n", mobs[i].hp);
            if(player.hp > 0 && mobs[i].hp > 0){
                if(c == 32){
                    if(critique == 0){ // Si le joueur fait un coup critique
                        if(esquive == 0){ // Si le mob esquive le coup critique
                            printf("Le mob esquive !\n");
                        }
                        else{
                            mobs[i].hp -= player.atk * 2; // Le mob perd 2 fois plus de vie
                            printf("Il reste %d points de vie au mob !\n", mobs[i].hp);
                        }
                    }
                    else{
                        if(esquive == 0){ // Si le mob esquive le coup
                            printf("Le mob esquive !\n");
                        }
                        else{
                            mobs[i].hp -= player.atk; // Le mob perd de la vie
                            printf("Il reste %d points de vie au mob !\n", mobs[i].hp);
                        }
                    }
                    
                    if(map[mobs[i].posY - 1][mobs[i].posX].crossable){
                        map[mobs[i].posY][mobs[i].posX].mobOn = 0;
                        mobs[i].posY --;
                        map[mobs[i].posY][mobs[i].posX].mobOn = 1;
                    }
                    
                    if(mobs[i].hp <= 0){
                        printf("Le mob %d est mort", i);
                        map[mobs[i].posY][mobs[i].posX].mobOn = 0;
                        
                        for(int j = i; j<nbMob; j++){
                            mobs[j] = mobs[j+1];
                            nbMob--;
                        }
                    }
                }
                else{
                    if(critique == 0){ // Si le mob fait un coup critique
                        if(esquive == 0){ // Si le joueur esquive le coup critique
                            printf("Vous esquivez !\n");
                        }
                        else{
                            player.hp -= mobs[i].atk * 2; // Le joueur perd 2 fois plus de vie
                            printf("Il vous reste %d hp !\n", player.hp);
                        }
                    }
                    else{
                        if(esquive == 0){ // Si le joueur esquive le coup
                            printf("Vous esquivez !\n");
                        }
                        else{
                            player.hp -= mobs[i].atk; // Le joueur perd de la vie
                            printf("Il vous reste %d hp !\n", player.hp);
                        }
                    }

                    if(player.hp <= 0){
                        printf("\n\nVous êtes mort !\n");
                        printf("Le jeu va s'arréter dans 5 secondes...\n");
                        sleep(5);
                        exit(0);
                    }
                }
            }
        }
        else if(map[mobs[i].posY - 1][mobs[i].posX].playerOn){ // Le mob est 1 case en dessous du joueur
            if(player.hp > 0 && mobs[i].hp > 0){
                if(c == 32){
                    if(critique == 0){ // Si le joueur fait un coup critique
                        if(esquive == 0){ // Si le mob esquive le coup critique
                            printf("Le mob esquive !\n");
                        }
                        else{
                            mobs[i].hp -= player.atk * 2; // Le mob perd 2 fois plus de vie
                            printf("Il reste %d points de vie au mob !\n", mobs[i].hp);
                        }
                    }
                    else{
                        if(esquive == 0){ // Si le mob esquive le coup
                            printf("Le mob esquive !\n");
                        }
                        else{
                            mobs[i].hp -= player.atk; // Le mob perd de la vie
                            printf("Il reste %d points de vie au mob !\n", mobs[i].hp);
                        }
                    }

                    if(map[mobs[i].posY + 1][mobs[i].posX].crossable){
                        map[mobs[i].posY][mobs[i].posX].mobOn = 0;
                        mobs[i].posY ++;
                        map[mobs[i].posY][mobs[i].posX].mobOn = 1;
                    }
                    
                    if(mobs[i].hp <= 0){
                        printf("Le mob %d est mort", i);
                        map[mobs[i].posY][mobs[i].posX].mobOn = 0;

                        for(int j = i; j<nbMob; j++){
                            mobs[j] = mobs[j+1];
                            nbMob--;
                        }
                    }
                }
                else{
                    if(critique == 0){ // Si le mob fait un coup critique
                        if(esquive == 0){ // Si le joueur esquive le coup critique
                            printf("Vous esquivez !\n");
                        }
                        else{
                            player.hp -= mobs[i].atk * 2; // Le joueur perd 2 fois plus de vie
                            printf("Il vous reste %d hp !\n", player.hp);
                        }
                    }
                    else{
                        if(esquive == 0){ // Si le joueur esquive le coup
                            printf("Vous esquivez !\n");
                        }
                        else{
                            player.hp -= mobs[i].atk; // Le joueur perd de la vie
                            printf("Il vous reste %d hp !\n", player.hp);
                        }
                    }

                    if(player.hp <= 0){
                        printf("\n\nVous êtes mort !\n");
                        printf("Le jeu va s'arréter dans 5 secondes...\n");
                        sleep(5);
                        exit(0);
                    }
                }
            }
        }
        else if(map[mobs[i].posY][mobs[i].posX - 1].playerOn){ // Le mob est 1 case à droite du joueur
            if(player.hp > 0 && mobs[i].hp > 0){
                if(c == 32){
                    if(critique == 0){ // Si le joueur fait un coup critique
                        if(esquive == 0){ // Si le mob esquive le coup critique
                            printf("Le mob esquive !\n");
                        }
                        else{
                            mobs[i].hp -= player.atk * 2; // Le mob perd 2 fois plus de vie
                            printf("Il reste %d points de vie au mob !\n", mobs[i].hp);
                        }
                    }
                    else{
                        if(esquive == 0){ // Si le mob esquive le coup
                            printf("Le mob esquive !\n");
                        }
                        else{
                            mobs[i].hp -= player.atk; // Le mob perd de la vie
                            printf("Il reste %d points de vie au mob !\n", mobs[i].hp);
                        }
                    }
                    
                    if(map[mobs[i].posY][mobs[i].posX + 1].crossable){
                        map[mobs[i].posY][mobs[i].posX].mobOn = 0;
                        mobs[i].posX ++;
                        map[mobs[i].posY][mobs[i].posX].mobOn = 1;
                    }
                    
                    if(mobs[i].hp <= 0){
                        printf("Le mob %d est mort", i);
                        map[mobs[i].posY][mobs[i].posX].mobOn = 0;

                        for(int j = i; j<nbMob; j++){
                            mobs[j] = mobs[j+1];
                            nbMob--;
                        }
                    }
                }
                else{
                    if(critique == 0){ // Si le mob fait un coup critique
                        if(esquive == 0){ // Si le joueur esquive le coup critique
                            printf("Vous esquivez !\n");
                        }
                        else{
                            player.hp -= mobs[i].atk * 2; // Le joueur perd 2 fois plus de vie
                            printf("Il vous reste %d hp !\n", player.hp);
                        }
                    }
                    else{
                        if(esquive == 0){ // Si le joueur esquive le coup
                            printf("Vous esquivez !\n");
                        }
                        else{
                            player.hp -= mobs[i].atk; // Le joueur perd de la vie
                            printf("Il vous reste %d hp !\n", player.hp);
                        }
                    }

                    if(player.hp <= 0){
                        printf("\n\nVous êtes mort !\n");
                        printf("Le jeu va s'arréter dans 5 secondes...\n");
                        sleep(5);
                        exit(0);
                    }
                }
            }
        }
        else if(map[mobs[i].posY][mobs[i].posX + 1].playerOn){ // Le mob est 1 case à gauche du joueur
            if(player.hp > 0 && mobs[i].hp > 0){
                if(c == 32){
                    if(critique == 0){ // Si le joueur fait un coup critique
                        if(esquive == 0){ // Si le mob esquive le coup critique
                            printf("Le mob esquive !\n");
                        }
                        else{
                            mobs[i].hp -= player.atk * 2; // Le mob perd 2 fois plus de vie
                            printf("Il reste %d points de vie au mob !\n", mobs[i].hp);
                        }
                    }
                    else{
                        if(esquive == 0){ // Si le mob esquive le coup
                            printf("Le mob esquive !\n");
                        }
                        else{
                            mobs[i].hp -= player.atk; // Le mob perd de la vie
                            printf("Il reste %d points de vie au mob !\n", mobs[i].hp);
                        }
                    }
                    
                    if(map[mobs[i].posY][mobs[i].posX - 1].crossable){
                        map[mobs[i].posY][mobs[i].posX].mobOn = 0;
                        mobs[i].posX --;
                        map[mobs[i].posY][mobs[i].posX].mobOn = 1;
                    }

                    if(mobs[i].hp <= 0){
                        printf("Le mob %d est mort", i);
                        map[mobs[i].posY][mobs[i].posX].mobOn = 0;

                        for(int j = i; j<nbMob; j++){
                            mobs[j] = mobs[j+1];
                            nbMob--;
                        }
                    }
                }
                else{
                    if(critique == 0){ // Si le mob fait un coup critique
                        if(esquive == 0){ // Si le joueur esquive le coup critique
                            printf("Vous esquivez !\n");
                        }
                        else{
                            player.hp -= mobs[i].atk * 2; // Le joueur perd 2 fois plus de vie
                            printf("Il vous reste %d hp !\n", player.hp);
                        }
                    }
                    else{
                        if(esquive == 0){ // Si le joueur esquive le coup
                            printf("Vous esquivez !\n");
                        }
                        else{
                            player.hp -= mobs[i].atk; // Le joueur perd de la vie
                            printf("Il vous reste %d hp !\n", player.hp);
                        }
                    }

                    if(player.hp <= 0){
                        printf("\n\nVous êtes mort !\n");
                        printf("Le jeu va s'arréter dans 5 secondes...\n");
                        sleep(5);
                        exit(0);
                    }
                }
            }
        }
    }
}

Mob getMob(int id){
    return mobs[id];
}

void setMob(int id, Mob mob){
    mobs[id] = mob;
}

void mallocMob(int size){
    mobs = (Mob*) malloc(size * sizeof(Mob));
}