#include "mob.h"

Mob mob = {"zombie", 10, 5, 0, 0};

// Fonction pour faire spawn un mob
void spawnMob(Bloc ** map, int size){
    int i,j;
    do{
        i = rand() % size;
        j = rand() % size;
    }while(!map[i][j].spawnable || map[i][j].chest); // On vérifie que le bloc est spawnable et qu'il n'y a pas de coffre
    mob.posX = j;
    mob.posY = i;
    map[i][j].mobOn = 1; // On met le mob sur la map
}

// Fonction pour faire bouger le mob
void moveMob(Bloc ** map, Player player, int size){
    if(abs(mob.posX - player.posX) < 20 && abs(mob.posY - player.posY) < 20){ // Si le joueur est à moins de 20 blocs du mob (agro du joueur)
        if(abs(player.posX - mob.posX) > abs(player.posY - mob.posY)){ // Si la distance entre le joueur et le mob est plus grande en x que en y (le mob se déplace en x)
            if(player.posX > mob.posX){
                if(map[mob.posY][mob.posX + 1].crossable){ // Si le bloc à droite du mob est crossable (déplacement vers la droite)
                    map[mob.posY][mob.posX].mobOn = 0;
                    mob.posX ++;
                    map[mob.posY][mob.posX].mobOn = 1;
                }
                else if(map[mob.posY][mob.posX + 1].playerOn){ // Si le bloc à droite du mob est le joueur (le mob attaque le joueur)
                    player.hp -= mob.atk;
                }
            }
            else{
                if(map[mob.posY][mob.posX - 1].crossable){ // Si le bloc à gauche du mob est crossable (déplacement vers la gauche)
                    map[mob.posY][mob.posX].mobOn = 0;
                    mob.posX --;
                    map[mob.posY][mob.posX].mobOn = 1;
                }
                else if(map[mob.posY][mob.posX - 1].playerOn){ // Si le bloc à gauche du mob est le joueur (le mob attaque le joueur)
                    player.hp -= mob.atk;
                }
            }
        }
        else{ // Si la distance entre le joueur et le mob est plus grande en y que en x (le mob se déplace en y)
            if(player.posY > mob.posY){
                if(map[mob.posY + 1][mob.posX].crossable){ // Si le bloc en dessous du mob est crossable (déplacement vers le bas)
                    map[mob.posY][mob.posX].mobOn = 0;
                    mob.posY ++;
                    map[mob.posY][mob.posX].mobOn = 1;
                }
                else if(map[mob.posY + 1][mob.posX].playerOn){ // Si le bloc en dessous du mob est le joueur (le mob attaque le joueur)
                    player.hp -= mob.atk;
                }
            }
            else{
                if(map[mob.posY - 1][mob.posX].crossable){ // Si le bloc au dessus du mob est crossable (déplacement vers le haut)
                    map[mob.posY][mob.posX].mobOn = 0;
                    mob.posY --;
                    map[mob.posY][mob.posX].mobOn = 1;
                }
                else if(map[mob.posY - 1][mob.posX].playerOn){ // Si le bloc au dessus du mob est le joueur (le mob attaque le joueur)
                    player.hp -= mob.atk;
                }
            }
        }
    }
    else{ // Si le joueur est à plus de 20 blocs du mob (déplacement aléatoire du mob)
        srand(time(NULL));
        int a = rand() % 4; // Choix aléatoire de la direction du mob
        switch (a)
        {
        case 0: // Déplacement vers le haut
            if(map[mob.posY - 1][mob.posX].crossable){
                map[mob.posY][mob.posX].mobOn = 0;
                mob.posY --;
                map[mob.posY][mob.posX].mobOn = 1;
            }
            break;
        case 1: // Déplacement vers le bas
            if(map[mob.posY + 1][mob.posX].crossable){
                map[mob.posY][mob.posX].mobOn = 0;
                mob.posY ++;
                map[mob.posY][mob.posX].mobOn = 1;
            }
            break;
        case 2: // Déplacement vers la gauche
            if(map[mob.posY][mob.posX - 1].crossable){
                map[mob.posY][mob.posX].mobOn = 0;
                mob.posX --;
                map[mob.posY][mob.posX].mobOn = 1;
            }
            break;
        case 3: // Déplacement vers la droite
            if(map[mob.posY][mob.posX + 1].crossable){
                map[mob.posY][mob.posX].mobOn = 0;
                mob.posX ++;
                map[mob.posY][mob.posX].mobOn = 1;
            }
            break;
        default:
            break;
        }
    }
}