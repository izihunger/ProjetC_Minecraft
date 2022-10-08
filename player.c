#include "player.h"


Player player = {"default", 0, 50, 0, 0, 0};

// Fonction pour spawn le joueur
void spawnPlayer(Bloc ** map,int size){
    int i, j;
    do{
        i = rand() % size;
        j = rand() % size;
    }while(!map[i][j].spawnable || map[i][j].chest); // On vérifie que le bloc est spawnable et qu'il n'y a pas de coffre
    player.posX = j;
    player.posY = i;
    map[i][j].playerOn = 1; // On met le joueur sur la map
}

// Fonction pour set la position du joueur lors du chargement d'une partie
void setPos(int x, int y){
    player.posX = x;
    player.posY = y;
}

// Fonction pour déplacer le joueur
void movePlayer(Bloc ** map, char c){
    switch (c)
    {
    case 'z': // Déplacement vers le haut
        if(map[player.posY - 1][player.posX].crossable){
            map[player.posY][player.posX].playerOn = 0;
            player.posY --;
            map[player.posY][player.posX].playerOn = 1;
        }
        break;
    case 's': // Déplacement vers le bas
        if(map[player.posY + 1][player.posX].crossable){
            map[player.posY][player.posX].playerOn = 0;
            player.posY ++;
            map[player.posY][player.posX].playerOn = 1;
        }
        break;
    case 'q': // Déplacement vers la gauche
        if(map[player.posY][player.posX - 1].crossable){
            map[player.posY][player.posX].playerOn = 0;
            player.posX --;
            map[player.posY][player.posX].playerOn = 1;
        }
        break;
    case 'd': // Déplacement vers la droite
        if(map[player.posY][player.posX + 1].crossable){
            map[player.posY][player.posX].playerOn = 0;
            player.posX ++;
            map[player.posY][player.posX].playerOn = 1;
        }
        break;
    case 't':
        actionBlocPlayer(map);
        break;
    default:
        break;
    }
}

// Fonction pour set le nom du joueur
void setPlayerName(char * name){
    player.name = name;
}


// Modif map : tree repere puis detruit mais display ne change pas
void actionBlocPlayer(Bloc ** map){
    if(map[player.posY-1][player.posX].id == 3 || map[player.posY+1][player.posX].id == 3 || map[player.posY][player.posX-1].id == 3 || map[player.posY][player.posX+1].id == 3){
        printf("Il y a un arbre à casser\n");
        if(map[player.posY-1][player.posX].id == 3){
            map[player.posY-1][player.posX] = Dirt;
        }
        else if(map[player.posY+1][player.posX].id == 3){
            map[player.posY+1][player.posX] = Dirt;
        }
        else if(map[player.posY][player.posX-1].id == 3){
            map[player.posY][player.posX-1] = Dirt;
        }
        else if(map[player.posY][player.posX+1].id == 3){
            map[player.posY][player.posX+1] = Dirt;
        }
    }
    else{
        printf("Pas d'arbre a casser\n");
    }
}

// Fonction pour récupérer les données du joueur
Player getPlayer(){
    return player;
}

void openChest(Bloc ** map){
    int i = 0;
    while (chest[i].posX != player.posX || chest[i].posY != player.posY)
    {
        i++;
    } 
    printf("Ce coffre contient %s et %s lequel voulez vous prendre ? (1 ou 2) : ", chest[i].items[0].name, chest[i].items[1].name);
    int choice;
    scanf("%d", &choice);
    if(choice == 1 || choice == 2){
        if(player.nbItems < 32){
            player.inventory[player.nbItems] = chest[i].items[choice-1];
            player.nbItems ++;
        }
    }
    map[player.posY][player.posX].chest = 0;
}

void displayInventory(){
    printf("\n\033[04mInventory :\033[00m\n\n");
    for (int i = 0; i < player.nbItems; i++)
    {
        printf("%s ", player.inventory[i].name);
        if((i == 7 && player.nbItems-1 > 7) || (i == 15 && player.nbItems-1 > 15) || (i == 23 && player.nbItems-1 > 23)) printf("\n-----------------------------------------------------------\n");
        else if(i != player.nbItems-1) printf("| ");
    }
    printf("\n\n");
}