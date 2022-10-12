#include "player.h"


Player player = {"default", 0, 50, 5, 0, 0, 0};

// Fonction pour spawn le joueur
void spawnPlayer(Bloc ** map,int size){
    int i, j;
    do{
        i = rand() % size;
        j = rand() % size;
    }while(!map[i][j].spawnable || map[i][j].chest); // On vérifie que le bloc est spawnable et qu'il n'y a pas de coffre
    player.posX = j;
    player.posY = i;
    map[i][j].playerOn = 1;
    spawnVision(map, size);
}

void spawnVision(Bloc ** map, int size){
    map[player.posY][player.posX].vision = 1;
    if(player.posY == 0 && player.posX == 0){
        map[player.posY][player.posX+1].vision = 1;
        map[player.posY+1][player.posX].vision = 1;
        map[player.posY+1][player.posX+1].vision = 1;
    }
    else if(player.posY == 0 && player.posX == size-1){
        map[player.posY][player.posX-1].vision = 1;
        map[player.posY+1][player.posX-1].vision = 1;
        map[player.posY+1][player.posX].vision = 1;
    }
    else if(player.posY == size-1 && player.posX == size-1){
        map[player.posY-1][player.posX].vision = 1;
        map[player.posY-1][player.posX-1].vision = 1;
        map[player.posY][player.posX-1].vision = 1;
    }
    else if(player.posY == size-1 && player.posX == 0){
        map[player.posY][player.posX+1].vision = 1;
        map[player.posY-1][player.posX+1].vision = 1;
        map[player.posY-1][player.posX].vision = 1;
    }
    else if(player.posY == 0){
        map[player.posY][player.posX+1].vision = 1;
        map[player.posY][player.posX-1].vision = 1;
        map[player.posY+1][player.posX].vision = 1;
        map[player.posY+1][player.posX+1].vision = 1;
        map[player.posY+1][player.posX-1].vision = 1;
    }
    else if(player.posX == 0){
        map[player.posY-1][player.posX].vision = 1;
        map[player.posY+1][player.posX].vision = 1;
        map[player.posY-1][player.posX+1].vision = 1;
        map[player.posY][player.posX+1].vision = 1;
        map[player.posY+1][player.posX+1].vision = 1;
    }
    else if(player.posX == size-1){
        map[player.posY-1][player.posX].vision = 1;
        map[player.posY+1][player.posX].vision = 1;
        map[player.posY-1][player.posX-1].vision = 1;
        map[player.posY][player.posX-1].vision = 1;
        map[player.posY+1][player.posX-1].vision = 1;
    }
    else if(player.posY == size-1){
        map[player.posY][player.posX+1].vision = 1;
        map[player.posY][player.posX-1].vision = 1;
        map[player.posY-1][player.posX].vision = 1;
        map[player.posY-1][player.posX+1].vision = 1;
        map[player.posY-1][player.posX-1].vision = 1;
    }
    else{
        map[player.posY][player.posX+1].vision = 1;
        map[player.posY][player.posX-1].vision = 1;
        map[player.posY+1][player.posX].vision = 1;
        map[player.posY-1][player.posX].vision = 1;
        map[player.posY+1][player.posX+1].vision = 1;
        map[player.posY-1][player.posX+1].vision = 1;
        map[player.posY+1][player.posX-1].vision = 1;
        map[player.posY-1][player.posX-1].vision = 1;
    }
}

void addVision(Bloc ** map, int size, char c, int maxrange){
    int allowVision = 1;
    switch (c)
    {
        case 'z':
            /*if(player.posY-1 >= 0){
                map[player.posY-1][player.posX].vision = 1;              
                if(player.posX-1 >= 0) map[player.posY-1][player.posX-1].vision = 1;
                if(player.posX+1 < size) map[player.posY-1][player.posX+1].vision = 1;
                if(player.posY-2 >= 0){
                    if(map[player.posY-1][player.posX].crossable && player.posY-2 >= 0){
                        map[player.posY-2][player.posX].vision = 1;
                        if(player.posX-1 >= 0) map[player.posY-2][player.posX-1].vision = 1;
                        if(player.posX+1 < size) map[player.posY-2][player.posX+1].vision = 1;
                    }
                    if(map[player.posY-1][player.posX-1].crossable && player.posX-1 >= 0 && player.posX-2 >= 0) map[player.posY-2][player.posX-2].vision = 1;
                    if(map[player.posY-1][player.posX+1].crossable && player.posX+1 < size && player.posX+2 < size) map[player.posY-2][player.posX+2].vision = 1;
                }
            }*/
            if(player.posY-1 >= 0){
                map[player.posY-1][player.posX].vision = 1;
                if(player.posX+1 < size){
                    map[player.posY-1][player.posX +1].vision = 1;
                    map[player.posY][player.posX+1].vision = 1;
                }
                if(player.posX-1 >= 0) {
                    map[player.posY-1][player.posX -1].vision = 1;
                    map[player.posY][player.posX-1].vision = 1;
                }
            }
            else break;
            if(map[player.posY-1][player.posX].crossable){
                for(int i = 2; i <= maxrange; i++){
                    if(player.posY-i >= 0){
                        for(int j = 1; j < i; j++){
                            if(!map[player.posY-j][player.posX].crossable) allowVision = 0;
                        }
                        if(allowVision) map[player.posY-i][player.posX].vision = 1;
                        allowVision = 1;
                        for(int j = 1; j < i; j++){
                            if(!map[player.posY-j][player.posX+1].crossable) allowVision = 0;
                        }
                        if(allowVision && player.posX+1 < size) map[player.posY-i][player.posX+1].vision = 1;
                        allowVision = 1;
                        for(int j = 1; j < i; j++){
                            if(!map[player.posY-j][player.posX-1].crossable) allowVision = 0;
                        }
                        if(allowVision && player.posX-1 >= 0) map[player.posY-i][player.posX-1].vision = 1;
                    }
                    else break;
                }
            }
            break;
        case 's':
            /*map[player.posY+1][player.posX].vision = 1;
            map[player.posY+1][player.posX-1].vision = 1;
            map[player.posY+1][player.posX+1].vision = 1;
            if(map[player.posY+1][player.posX].crossable){
                map[player.posY+2][player.posX].vision = 1;
                map[player.posY+2][player.posX-1].vision = 1;
                map[player.posY+2][player.posX+1].vision = 1;
            } 
            if(map[player.posY+1][player.posX-1].crossable) map[player.posY+2][player.posX-2].vision = 1;
            if(map[player.posY+1][player.posX+1].crossable) map[player.posY+2][player.posX+2].vision = 1;
            break;*/
            if(player.posY+1 < size){
                map[player.posY+1][player.posX].vision = 1;
                if(player.posX+1 < size){
                    map[player.posY+1][player.posX +1].vision = 1;
                    map[player.posY][player.posX +1].vision = 1;
                }
                if(player.posX-1 >= 0) {
                    map[player.posY+1][player.posX -1].vision = 1;
                    map[player.posY][player.posX -1].vision = 1;
                }
            }
            else break;
            if(map[player.posY+1][player.posX].crossable){
                for(int i = 2; i <= maxrange; i++){
                    if(player.posY+i < size){
                        for(int j = 1; j < i; j++){
                            if(!map[player.posY+j][player.posX].crossable) allowVision = 0;
                        }
                        if(allowVision) map[player.posY+i][player.posX].vision = 1;
                        allowVision = 1;
                        for(int j = 1; j < i; j++){
                            if(!map[player.posY+j][player.posX+1].crossable) allowVision = 0;
                        }
                        if(allowVision && player.posX+1 < size) map[player.posY+i][player.posX+1].vision = 1;
                        allowVision = 1;
                        for(int j = 1; j < i; j++){
                            if(!map[player.posY+j][player.posX-1].crossable) allowVision = 0;
                        }
                        if(allowVision && player.posX-1 >= 0) map[player.posY+i][player.posX-1].vision = 1;
                    }
                    else break;
                }
            }
            break;
        case 'q':
            /*map[player.posY][player.posX-1].vision = 1;
            map[player.posY-1][player.posX-1].vision = 1;
            map[player.posY+1][player.posX-1].vision = 1;
            if(map[player.posY][player.posX-1].crossable){
                map[player.posY][player.posX-2].vision = 1;
                map[player.posY-1][player.posX-2].vision = 1;
                map[player.posY+1][player.posX-2].vision = 1;
            } 
            if(map[player.posY-1][player.posX-1].crossable) map[player.posY-2][player.posX-2].vision = 1;
            if(map[player.posY+1][player.posX-1].crossable) map[player.posY+2][player.posX-2].vision = 1;
            break;*/
            if(player.posX-1 >= 0){
                map[player.posY][player.posX-1].vision = 1;
                if(player.posY+1 < size){
                    map[player.posY+1][player.posX -1].vision = 1;
                    map[player.posY+1][player.posX].vision = 1;
                } 
                if(player.posY-1 >= 0) {
                    map[player.posY-1][player.posX -1].vision = 1;
                    map[player.posY-1][player.posX].vision = 1;
                }
            }
            else break;
            if(map[player.posY][player.posX-1].crossable){
                for(int i = 2; i <= maxrange; i++){
                    if(player.posX-i >= 0){
                        for(int j = 1; j < i; j++){
                            if(!map[player.posY][player.posX-j].crossable) allowVision = 0;
                        }
                        if(allowVision) map[player.posY][player.posX-i].vision = 1;
                        allowVision = 1;
                        for(int j = 1; j < i; j++){
                            if(!map[player.posY+1][player.posX-j].crossable) allowVision = 0;
                        }
                        if(allowVision && player.posY+1 < size) map[player.posY+1][player.posX-i].vision = 1;
                        allowVision = 1;
                        for(int j = 1; j < i; j++){
                            if(!map[player.posY-1][player.posX-j].crossable) allowVision = 0;
                        }
                        if(allowVision && player.posY-1 >= 0) map[player.posY-1][player.posX-i].vision = 1;
                    }
                    else break;
                }
            }
            break;
        case 'd':
            /*map[player.posY][player.posX+1].vision = 1;
            map[player.posY-1][player.posX+1].vision = 1;
            map[player.posY+1][player.posX+1].vision = 1;
            if(map[player.posY][player.posX+1].crossable){
                map[player.posY][player.posX+2].vision = 1;
                map[player.posY-1][player.posX+2].vision = 1;
                map[player.posY+1][player.posX+2].vision = 1;
            } 
            if(map[player.posY-1][player.posX-1].crossable) map[player.posY-2][player.posX-2].vision = 1;
            if(map[player.posY+1][player.posX-1].crossable) map[player.posY+2][player.posX-2].vision = 1;
            break;*/
            if(player.posX+1 < size){
                map[player.posY][player.posX+1].vision = 1;
                if(player.posY+1 < size) {
                    map[player.posY+1][player.posX +1].vision = 1;
                    map[player.posY+1][player.posX].vision = 1;
                }
                if(player.posY-1 >= 0) {
                    map[player.posY-1][player.posX +1].vision = 1;
                    map[player.posY-1][player.posX].vision = 1;
                }
            }
            else break;
            if(map[player.posY][player.posX+1].crossable){
                for(int i = 2; i <= maxrange; i++){
                    if(player.posX+i < size){
                        for(int j = 1; j < i; j++){
                            if(!map[player.posY][player.posX+j].crossable) allowVision = 0;
                        }
                        if(allowVision) map[player.posY][player.posX+i].vision = 1;
                        allowVision = 1;
                        for(int j = 1; j < i; j++){
                            if(!map[player.posY+1][player.posX+j].crossable) allowVision = 0;
                        }
                        if(allowVision && player.posY+1 < size) map[player.posY+1][player.posX+i].vision = 1;
                        allowVision = 1;
                        for(int j = 1; j < i; j++){
                            if(!map[player.posY-1][player.posX+j].crossable) allowVision = 0;
                        }
                        if(allowVision && player.posY-1 >= 0) map[player.posY-1][player.posX+i].vision = 1;
                    }
                    else break;
                }
            }
            break;
        default:
            break;
    }
}

// Fonction pour set la position du joueur lors du chargement d'une partie
void setPos(int x, int y){
    player.posX = x;
    player.posY = y;
}

// Fonction pour déplacer le joueur
void movePlayer(Bloc ** map, int size, char c){
    switch (c)
    {
    case 'z': // Déplacement vers le haut
        if(player.posY-1 >= 0){
            if(map[player.posY - 1][player.posX].crossable){
                map[player.posY][player.posX].playerOn = 0;
                player.posY --;
                map[player.posY][player.posX].playerOn = 1;
            }
            //displayPlayer = "\033[36m\36 \033[37m";
            addVision(map, size, c, 3);
        }
        break;
    case 's': // Déplacement vers le bas
        if(player.posY+1 < size){
            if(map[player.posY + 1][player.posX].crossable){
                map[player.posY][player.posX].playerOn = 0;
                player.posY ++;
                map[player.posY][player.posX].playerOn = 1;
            }
            //displayPlayer = "\033[36m\37 \033[37m";
            addVision(map, size, c, 3);
        }   
        break;
    case 'q': // Déplacement vers la gauche
        if(player.posX-1 >= 0){
            if(map[player.posY][player.posX - 1].crossable){
                map[player.posY][player.posX].playerOn = 0;
                player.posX --;
                map[player.posY][player.posX].playerOn = 1;
            }
            //displayPlayer = "\033[36m\21 \033[37m";
            addVision(map, size, c, 3);
        }
        break;
    case 'd': // Déplacement vers la droite
        if(player.posX+1 < size){
            if(map[player.posY][player.posX + 1].crossable){
                map[player.posY][player.posX].playerOn = 0;
                player.posX ++;
                map[player.posY][player.posX].playerOn = 1;
            }
            //displayPlayer = "\033[36m\20 \033[37m";
            addVision(map, size, c, 3);
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
    printf("Vous êtes sur un coffre !\nCe coffre contient %s et %s lequel voulez vous prendre ? (1 ou 2) : ", chest[i].items[0].name, chest[i].items[1].name);
    int choice;
    if(scanf("%d", &choice)){
        if(choice == 1 || choice == 2){
            if(player.nbItems < 32){
                player.inventory[player.nbItems] = chest[i].items[choice-1];
                player.nbItems ++;
            }
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