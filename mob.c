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
void moveMob(Bloc ** map, int size){
    for(int i = 0; i<nbMob; i++){
        int move = rand() % 4; // On génère un nombre entre 0 et 3 pour déterminer si le mob bouge ou pas
        if(move != 0){
            if(abs(mobs[i].posX - player.posX) < 20 && abs(mobs[i].posY - player.posY) < 20){ // Si le joueur est à moins de 20 blocs du mob (agro du joueur)
                if(abs(player.posX - mobs[i].posX) > abs(player.posY - mobs[i].posY)){ // Si la distance entre le joueur et le mob est plus grande en x que en y (le mob se déplace en x)
                    if(player.posX > mobs[i].posX){
                        if(mobs[i].posX+1 < size){
                            if(map[mobs[i].posY][mobs[i].posX + 1].crossable && !map[mobs[i].posY][mobs[i].posX + 1].playerOn && !map[mobs[i].posY][mobs[i].posX + 1].mobOn){ // Si le bloc à droite du mob est crossable (déplacement vers la droite)
                                map[mobs[i].posY][mobs[i].posX].mobOn = 0;
                                mobs[i].posX ++;
                                map[mobs[i].posY][mobs[i].posX].mobOn = 1;
                            }
                        }
                    }
                    else{
                        if(mobs[i].posX-1 >= 0){
                            if(map[mobs[i].posY][mobs[i].posX - 1].crossable && !map[mobs[i].posY][mobs[i].posX - 1].playerOn && !map[mobs[i].posY][mobs[i].posX - 1].mobOn){ // Si le bloc à gauche du mob est crossable (déplacement vers la gauche)
                                map[mobs[i].posY][mobs[i].posX].mobOn = 0;
                                mobs[i].posX --;
                                map[mobs[i].posY][mobs[i].posX].mobOn = 1;
                            }
                        }
                    }
                }
                else{ // Si la distance entre le joueur et le mob est plus grande en y que en x (le mob se déplace en y)
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

int critique(){
    return rand() % 5;
}

int esquive(){
    return rand() % 4;
}

int fight(Bloc ** map, int size){
    for(int i = 0; i < player.nbItems; i++){
        if (player.inventory[i].id == 0){
            player.atk += 3;
            break;
        } 
    }
    for(int i = 0; i < player.nbItems; i++){
        if (player.inventory[i].id == 3){
            player.res += 3;
            break;
        } 
    }
    char fin;
    for(int i = 0; i<nbMob; i++){
        if(mobs[i].posY + 1 < size && map[mobs[i].posY + 1][mobs[i].posX].playerOn){ // Le mob est 1 case au dessus du joueur
            if(player.hp > 0 && mobs[i].hp > 0){
                printf("\r\n\r\n");
                if(!critique()){ // Si le joueur fait un coup critique
                    if(!esquive()){ // Si le mob esquive le coup critique
                        printf("Le mob esquive !\r\n");
                    }
                    else{
                        mobs[i].hp -= player.atk * 2; // Le mob perd 2 fois plus de vie
                        printf("Il reste %d points de vie au mob !\r\n", mobs[i].hp);
                    }
                }
                else{
                    if(!esquive()){ // Si le mob esquive le coup
                        printf("Le mob esquive !\r\n");
                    }
                    else{
                        mobs[i].hp -= player.atk; // Le mob perd de la vie
                        printf("Il reste %d points de vie au mob !\r\n", mobs[i].hp);
                    }
                }

                if(mobs[i].hp <= 0){
                    printf("Le mob %d est mort\r\n", i);
                    map[mobs[i].posY][mobs[i].posX].mobOn = 0;
                    
                    for(int j = i; j<nbMob-1; j++){
                        mobs[j] = mobs[j+1];
                    }
                    nbMob--;
                }
                else if(!critique()){ // Si le mob fait un coup critique
                    if(!esquive()){ // Si le joueur esquive le coup critique
                        printf("Vous esquivez !\r\n");
                    }
                    else{
                        player.hp -= mobs[i].atk * 2 - player.res; // Le joueur perd 2 fois plus de vie
                        printf("Il vous reste %d hp !\r\n", player.hp);
                    }
                    /*if(mobs[i].posY - 1 >= 0 && map[mobs[i].posY - 1][mobs[i].posX].crossable){
                        map[mobs[i].posY][mobs[i].posX].mobOn = 0;
                        mobs[i].posY --;
                        map[mobs[i].posY][mobs[i].posX].mobOn = 1;
                    }*/
                }
                else{
                    if(!esquive()){ // Si le joueur esquive le coup
                        printf("Vous esquivez !\r\n");
                    }
                    else{
                        player.hp -= mobs[i].atk - player.res; // Le joueur perd de la vie
                        printf("Il vous reste %d hp !\r\n", player.hp);
                    }
                    /*if(mobs[i].posY - 1 >= 0 && map[mobs[i].posY - 1][mobs[i].posX].crossable){
                        map[mobs[i].posY][mobs[i].posX].mobOn = 0;
                        mobs[i].posY --;
                        map[mobs[i].posY][mobs[i].posX].mobOn = 1;
                    }*/
                }

                if(player.hp <= 0){
                    printf("\n\nVous êtes mort !\r\n");
                    printf("Le jeu va s'arréter dans 5 secondes...\r\n");
                    sleep(5);
                    return 0;
                }
                printf("\r\nAppuyer sur la touche entrer pour continuer...");
                scanf("%c", &fin);
            }
        }
        else if(mobs[i].posY - 1 >= 0 && map[mobs[i].posY - 1][mobs[i].posX].playerOn){ // Le mob est 1 case en dessous du joueur
            if(player.hp > 0 && mobs[i].hp > 0){
                printf("\r\n\r\n");
                if(!critique()){ // Si le joueur fait un coup critique
                    if(!esquive()){ // Si le mob esquive le coup critique
                        printf("Le mob esquive !\r\n");
                    }
                    else{
                        mobs[i].hp -= player.atk * 2; // Le mob perd 2 fois plus de vie
                        printf("Il reste %d points de vie au mob !\r\n", mobs[i].hp);
                    }
                }
                else{
                    if(!esquive()){ // Si le mob esquive le coup
                        printf("Le mob esquive !\r\n");
                    }
                    else{
                        mobs[i].hp -= player.atk; // Le mob perd de la vie
                        printf("Il reste %d points de vie au mob !\r\n", mobs[i].hp);
                    }
                }

                if(mobs[i].hp <= 0){
                    printf("Le mob %d est mort\r\n", i);
                    map[mobs[i].posY][mobs[i].posX].mobOn = 0;
                    
                    for(int j = i; j<nbMob-1; j++){
                        mobs[j] = mobs[j+1];
                    }
                    nbMob--;
                }
                else if(!critique()){ // Si le mob fait un coup critique
                    if(!esquive()){ // Si le joueur esquive le coup critique
                        printf("Vous esquivez !\r\n");
                    }
                    else{
                        player.hp -= mobs[i].atk * 2 - player.res; // Le joueur perd 2 fois plus de vie
                        printf("Il vous reste %d hp !\r\n", player.hp);
                    }
                    /*if(mobs[i].posY + 1 < size && map[mobs[i].posY + 1][mobs[i].posX].crossable){
                        map[mobs[i].posY][mobs[i].posX].mobOn = 0;
                        mobs[i].posY ++;
                        map[mobs[i].posY][mobs[i].posX].mobOn = 1;
                    }*/
                }
                else{
                    if(!esquive()){ // Si le joueur esquive le coup
                        printf("Vous esquivez !\r\n");
                    }
                    else{
                        player.hp -= mobs[i].atk - player.res; // Le joueur perd de la vie
                        printf("Il vous reste %d hp !\r\n", player.hp);
                    }
                    /*if(mobs[i].posY + 1 < size && map[mobs[i].posY + 1][mobs[i].posX].crossable){
                        map[mobs[i].posY][mobs[i].posX].mobOn = 0;
                        mobs[i].posY ++;
                        map[mobs[i].posY][mobs[i].posX].mobOn = 1;
                    }*/
                }

                if(player.hp <= 0){
                    printf("\n\nVous êtes mort !\r\n");
                    printf("Le jeu va s'arréter dans 5 secondes...\r\n");
                    sleep(5);
                    return 0;
                }
                printf("\r\nAppuyer sur la touche entrer pour continuer...");
                scanf("%c", &fin);
            }
        }
        else if(mobs[i].posX - 1 >= 0 && map[mobs[i].posY][mobs[i].posX - 1].playerOn){ // Le mob est 1 case à droite du joueur
            if(player.hp > 0 && mobs[i].hp > 0){
                printf("\r\n\r\n");
                if(!critique()){ // Si le joueur fait un coup critique
                    if(!esquive()){ // Si le mob esquive le coup critique
                        printf("Le mob esquive !\r\n");
                    }
                    else{
                        mobs[i].hp -= player.atk * 2; // Le mob perd 2 fois plus de vie
                        printf("Il reste %d points de vie au mob !\r\n", mobs[i].hp);
                    }
                }
                else{
                    if(!esquive()){ // Si le mob esquive le coup
                        printf("Le mob esquive !\r\n");
                    }
                    else{
                        mobs[i].hp -= player.atk; // Le mob perd de la vie
                        printf("Il reste %d points de vie au mob !\r\n", mobs[i].hp);
                    }
                }

                if(mobs[i].hp <= 0){
                    printf("Le mob %d est mort\r\n", i);
                    map[mobs[i].posY][mobs[i].posX].mobOn = 0;
                    
                    for(int j = i; j<nbMob-1; j++){
                        mobs[j] = mobs[j+1];
                    }
                    nbMob--;
                }
                else if(!critique()){ // Si le mob fait un coup critique
                    if(!esquive()){ // Si le joueur esquive le coup critique
                        printf("Vous esquivez !\r\n");
                    }
                    else{
                        player.hp -= mobs[i].atk * 2 - player.res; // Le joueur perd 2 fois plus de vie
                        printf("Il vous reste %d hp !\r\n", player.hp);
                    }
                    /*if(mobs[i].posX + 1 < size && map[mobs[i].posY][mobs[i].posX + 1].crossable){
                        map[mobs[i].posY][mobs[i].posX].mobOn = 0;
                        mobs[i].posX ++;
                        map[mobs[i].posY][mobs[i].posX].mobOn = 1;
                    }*/
                }
                else{
                    if(!esquive()){ // Si le joueur esquive le coup
                        printf("Vous esquivez !\r\n");
                    }
                    else{
                        player.hp -= mobs[i].atk - player.res; // Le joueur perd de la vie
                        printf("Il vous reste %d hp !\r\n", player.hp);
                    }
                    /*if(mobs[i].posX + 1 < size && map[mobs[i].posY][mobs[i].posX + 1].crossable){
                        map[mobs[i].posY][mobs[i].posX].mobOn = 0;
                        mobs[i].posX ++;
                        map[mobs[i].posY][mobs[i].posX].mobOn = 1;
                    }*/
                }

                if(player.hp <= 0){
                    printf("\n\nVous êtes mort !\r\n");
                    printf("Le jeu va s'arréter dans 5 secondes...\r\n");
                    sleep(5);
                    return 0;
                }
                printf("\r\nAppuyer sur la touche entrer pour continuer...");
                scanf("%c", &fin);
            }
        }
        else if(mobs[i].posX + 1 < size && map[mobs[i].posY][mobs[i].posX + 1].playerOn){ // Le mob est 1 case à gauche du joueur
            if(player.hp > 0 && mobs[i].hp > 0){
                printf("\r\n\r\n");
                if(!critique()){ // Si le joueur fait un coup critique
                    if(!esquive()){ // Si le mob esquive le coup critique
                        printf("Le mob esquive !\r\n");
                    }
                    else{
                        mobs[i].hp -= player.atk * 2; // Le mob perd 2 fois plus de vie
                        printf("Il reste %d points de vie au mob !\r\n", mobs[i].hp);
                    }
                }
                else{
                    if(!esquive()){ // Si le mob esquive le coup
                        printf("Le mob esquive !\r\n");
                    }
                    else{
                        mobs[i].hp -= player.atk; // Le mob perd de la vie
                        printf("Il reste %d points de vie au mob !\r\n", mobs[i].hp);
                    }
                }

                if(mobs[i].hp <= 0){
                    printf("Le mob %d est mort\r\n", i);
                    map[mobs[i].posY][mobs[i].posX].mobOn = 0;
                    
                    for(int j = i; j<nbMob-1; j++){
                        mobs[j] = mobs[j+1];
                    }
                    nbMob--;
                }
                else if(!critique()){ // Si le mob fait un coup critique
                    if(!esquive()){ // Si le joueur esquive le coup critique
                        printf("Vous esquivez !\r\n");
                    }
                    else{
                        player.hp -= mobs[i].atk * 2 - player.res; // Le joueur perd 2 fois plus de vie
                        printf("Il vous reste %d hp !\r\n", player.hp);
                    }
                    /*if(mobs[i].posX - 1 >= 0 && map[mobs[i].posY][mobs[i].posX - 1].crossable){
                        map[mobs[i].posY][mobs[i].posX].mobOn = 0;
                        mobs[i].posX --;
                        map[mobs[i].posY][mobs[i].posX].mobOn = 1;
                    }*/
                }
                else{
                    if(!esquive()){ // Si le joueur esquive le coup
                        printf("Vous esquivez !\r\n");
                    }
                    else{
                        player.hp -= mobs[i].atk - player.res; // Le joueur perd de la vie
                        printf("Il vous reste %d hp !\r\n", player.hp);
                    }
                    /*if(mobs[i].posX - 1 >= 0 && map[mobs[i].posY][mobs[i].posX - 1].crossable){
                        map[mobs[i].posY][mobs[i].posX].mobOn = 0;
                        mobs[i].posX --;
                        map[mobs[i].posY][mobs[i].posX].mobOn = 1;
                    }*/
                }

                if(player.hp <= 0){
                    printf("\n\nVous êtes mort !\r\n");
                    printf("Le jeu va s'arréter dans 5 secondes...\r\n");
                    sleep(5);
                    return 0;
                }
                printf("\r\nAppuyer sur la touche entrer pour continuer...");
                scanf("%c", &fin);
            }
        }
    }
    return 1;
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