#include "player.h"


Player player = {"default", 1, 0, 50, 0, 5, 0, 0, 0};

// Fonction to spawn the player
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

// Function to allow the vision of the player when he spawns
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

// Function to allow the vision of the player when he moves
void addVision(Bloc ** map, int size, char c, int maxrange){
    int allowVision = 1;
    switch (c)
    {
        case 'z':
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
                            if(player.posY+1 < size) if(!map[player.posY+1][player.posX-j].crossable) allowVision = 0;
                        }
                        if(player.posY+1 < size && allowVision) map[player.posY+1][player.posX-i].vision = 1;
                        allowVision = 1;
                        for(int j = 1; j < i; j++){
                            if(player.posY-1 >= 0) if(!map[player.posY-1][player.posX-j].crossable) allowVision = 0;
                        }
                        if(allowVision && player.posY-1 >= 0) map[player.posY-1][player.posX-i].vision = 1;
                    }
                    else break;
                }
            }
            break;
        case 'd':
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
                            if(player.posY+1 < size) if(!map[player.posY+1][player.posX+j].crossable) allowVision = 0;
                        }
                        if(allowVision && player.posY+1 < size) map[player.posY+1][player.posX+i].vision = 1;
                        allowVision = 1;
                        for(int j = 1; j < i; j++){
                            if(player.posY-1 >= 0) if(!map[player.posY-1][player.posX+j].crossable) allowVision = 0;
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
            if(map[player.posY - 1][player.posX].crossable && !map[player.posY - 1][player.posX].mobOn){
                map[player.posY][player.posX].playerOn = 0;
                player.posY --;
                map[player.posY][player.posX].playerOn = 1;
            }
            displayPlayer = "\033[36mᐃ \033[37m";
            addVision(map, size, c, 3);
        }
        break;
    case 's': // Déplacement vers le bas
        if(player.posY+1 < size){
            if(map[player.posY + 1][player.posX].crossable && !map[player.posY + 1][player.posX].mobOn){
                map[player.posY][player.posX].playerOn = 0;
                player.posY ++;
                map[player.posY][player.posX].playerOn = 1;
            }
            displayPlayer = "\033[36mᐁ \033[37m";
            addVision(map, size, c, 3);
        }   
        break;
    case 'q': // Déplacement vers la gauche
        if(player.posX-1 >= 0){
            if(map[player.posY][player.posX - 1].crossable && !map[player.posY][player.posX - 1].mobOn){
                map[player.posY][player.posX].playerOn = 0;
                player.posX --;
                map[player.posY][player.posX].playerOn = 1;
            }
            displayPlayer = "\033[36mᐊ \033[37m";
            addVision(map, size, c, 3);
        }
        break;
    case 'd': // Déplacement vers la droite
        if(player.posX+1 < size){
            if(map[player.posY][player.posX + 1].crossable && !map[player.posY][player.posX + 1].mobOn){
                map[player.posY][player.posX].playerOn = 0;
                player.posX ++;
                map[player.posY][player.posX].playerOn = 1;
            }
            displayPlayer = "\033[36mᐅ \033[37m";
            addVision(map, size, c, 3);
        }
        break;
    case 't':
        actionBlocPlayer(map, size);
        break;
    default:
        break;
    }
}

// Modif map : tree repere puis detruit mais display ne change pas
void actionBlocPlayer(Bloc ** map, int size){
    if(player.posY-1 >= 0){
        if(map[player.posY-1][player.posX].id == 3){
            map[player.posY-1][player.posX] = Dirt;
            map[player.posY-1][player.posX].vision = 1;
        }
    }
    if(player.posY+1 < size){
        if(map[player.posY+1][player.posX].id == 3){
            map[player.posY+1][player.posX] = Dirt;
            map[player.posY+1][player.posX].vision = 1;
        }
    }
    if(player.posX-1 >= 0){
        if(map[player.posY][player.posX-1].id == 3){
            map[player.posY][player.posX-1] = Dirt;
            map[player.posY][player.posX-1].vision = 1;
        }
    }
    if(player.posX+1 < size){
        if(map[player.posY][player.posX+1].id == 3){
            map[player.posY][player.posX+1] = Dirt;
            map[player.posY][player.posX+1].vision = 1;
        }
    }
}

// Fonction pour récupérer les données du joueur
Player getPlayer(){
    return player;
}

// Function to open a chest
void openChest(Bloc ** map){
    int i = 0;
    while (chest[i].posX != player.posX || chest[i].posY != player.posY)
    {
        i++;
    } 
    printf("Vous etes sur un coffre !\nCe coffre contient un(e) %s et un(e) %s lequel voulez vous prendre ? (1 ou 2) : ", chest[i].items[0].name, chest[i].items[1].name);
    int choice;
    if(scanf("%d", &choice)){
        if(choice == 1 || choice == 2){
            if(player.nbItems < nbItemMax){
                player.inventory[player.nbItems] = chest[i].items[choice-1];
                player.nbItems ++;
            }
        }
    }
    map[player.posY][player.posX].chest = 0;
}

// Fonction to displau the player inventory
void displayInventory(){
    printf("\n\033[04mInventory :\033[00m\n\n");
    for (int i = 0; i < player.nbItems; i++)
    {
        printf("%s ", player.inventory[i].name);
        if((i == 7 && player.nbItems-1 > 7) || (i == 15 && player.nbItems-1 > 15) || (i == 23 && player.nbItems-1 > 23)) printf("\n-----------------------------------------------------------\n");
        else if(i != player.nbItems-1) printf("| ");
    }
    printf("\n\n");
    char fin;
    printf("Appuyer sur entrée pour reafficher la map...");
    scanf("%c", &fin);
}

// Function to eat food for regeneration
void manger(){
    printf("\r\n\r\nVous pouvez mangez :\r\n\n"); 
    int manger = 0;   
    for (int i = 0; i < player.nbItems; i++){
        if(player.inventory[i].id == 1 || player.inventory[i].id == 2 || player.inventory[i].id == 4){
            manger = 1;
            printf("- %s (Numero %d)\r\n", player.inventory[i].name, i);
        }
    }
    if(manger){
        printf("\r\nEntrez le numéro de la nourriture que vous souhaitez manger : "); 
        int choice;
        scanf("%d", &choice);
        for (int i = player.nbItems - 1; i > choice; i--){
            player.inventory[i-1] = player.inventory[i];
        }
        player.nbItems --;
        player.hp += 10;
    }
    else printf("\r\nVous n'avez pas de nourriture dans votre inventaire !\r\n"); 
}

// Function to show the player XP and level
void displayPlayerXP(){
    printf("Vous êtes niveau %d (%dxp/%dxp).\r\n", player.level, player.xp, 100 * power(2, player.level));
}