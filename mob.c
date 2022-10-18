#include "mob.h"

Mob mob = {"zombie", 20, 8, 0, 0};

Mob * mobs;
int nbMob = 0;

// Fonction pour faire spawn un mob
void spawnMob(Bloc ** map, int size){
    int i,j;
    do{
        i = rand() % size;
        j = rand() % size;
    }while(!map[i][j].spawnable || map[i][j].chest || map[i][j].playerOn || map[i][j].mobOn); // On vérifie que le bloc est spawnable et qu'il n'y a pas de coffre
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
}

// Fonction pour faire bouger le mob
void moveMob(Bloc ** map, Player player, int size){
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

void fightMob(Bloc ** map, Mob mob, Player player, char c){
    system("clear");
    printf("Un %s apparaît !\n", mob.name);
    
    while(mob.hp > 0 && player.hp > 0){
        printf("Santé du %s : %d\t     ▼\n      ▲\tAttaque du %s : %d\t      \nSanté de %s : %d\t     ▼\n      ▲\tAttaque de %s : %d\t      \n",
            mob.name, mob.hp, mob.name, mob.atk, player.name, player.hp, player.name, player.atk);
        for(int i=0; i<10; i++){
            printf("-");
        }
        printf("\n\nQue voulez-vous faire ?\n 1: Combattre\n 2: Regarder votre sac à dos\n 3: Prendre la fuite\n");
        
        while(c != '1' && c != '2' && c != '3'){
            scanf("%c", &c);
        }

        if(c == '1'){
            srand(time(NULL));
            int quiATK = rand() % 2; //Détermine qui commence
            if(quiATK == 1){
                int coupCritique = rand() % 5; //20% chance de faire un coup critique
                int coupEsquive = rand() % 4; //25% chance d'esquiver le coup
                printf("%s commence à attaquer !\n", player.name);

                for(int i=0; i<32; i++){
                    if(player.inventory[i].id == 1){ //Si le player a une épée
                        player.atk += 5;
                        if(coupCritique == 0){ //Si est un coup critique
                            player.atk += 5;
                            if(coupEsquive == 0){ //le mob esquive le coup
                                player.atk = player.atk / 2;
                                mob.hp -= player.atk;
                                quiATK = 0;
                                printf("Le %s a esquivé un coup critique, il lui reste %d pv", mob.name, mob.hp);
                            }
                            else{
                                mob.hp -= player.atk;
                                quiATK = 0;
                                printf("Vous avez infligé un coup critique au %s ! Il lui reste %d pv", mob.name, mob.hp);
                            }
                        }
                        else{ //Si n'est pas un coup critique
                            if(coupEsquive == 0){ //Le mob esquive
                                player.atk = player.atk / 2;
                                mob.hp -= player.atk;
                                quiATK = 0;
                                printf("Le %s a esquivé le coup, il lui reste %d pv", mob.name, mob.hp);
                            }
                            else{
                                mob.hp -= player.atk;
                                quiATK = 0;
                                printf("Vous avez infligé %d pv de dégats au %s, il lui reste %d pv", player.atk, mob.name, mob.hp);
                            }
                        }
                    }
                    else{ // Si le joueur n'a pas d'épée
                        if(coupCritique == 0){ //Si est un coup critique
                            player.atk += 5;
                            if(coupEsquive == 0){ //Le mob esquive
                                player.atk = player.atk / 2;
                                mob.hp -= player.atk;
                                quiATK = 0;
                                printf("Le %s a esquivé un coup critique, il lui reste %d pv", mob.name, mob.hp);
                            }
                            else{
                                mob.hp -= player.atk;
                                quiATK = 0;
                                printf("Vous avez infligé un coup critique au %s ! Il lui reste %d pv", mob.name, mob.hp);
                            }
                        }
                        else{ //Si n'est pas un coup critique
                            if(coupEsquive == 0){ //Le mob esquive
                                player.atk = player.atk / 2;
                                mob.hp -= player.atk;
                                quiATK = 0;
                                printf("Le %s a esquivé le coup, il lui reste %d pv", mob.name, mob.hp);
                            }
                            else{
                                mob.hp -= player.atk;
                                quiATK = 0;
                                printf("Vous avez infligé %d pv de dégats au %s, il lui reste %d pv", player.atk, mob.name, mob.hp);
                            }
                        }
                    }
                }
            }
            else if(quiATK == 0){ //Le mob commence à attaquer
                srand(time(NULL));
                int coupEsquive = rand() % 4; //25% chance d'esquiver le coup
                printf("Le %s commence à attaquer !\n", mob.name);
                if(coupEsquive == 0){
                    mob.atk = mob.atk / 2;
                    player.hp -= mob.atk;
                    quiATK = 1;
                    printf("Vous avez esquivé le coup du %s, il vous reste %d pv", mob.name, player.hp);
                }
                else{
                    player.hp -= mob.atk;
                    quiATK = 1;
                    printf("Un %s vous a touché, il vous reste %d pv", mob.name, player.hp);
                }
            }
        }
        else if(c == '2'){
            system("clear");
            displayInventory();
            for(int i=0; i<32; i++){
                if(player.inventory[i].id == 2 || player.inventory[i].id == 4){
                    printf("Voulez-vous manger pour régénérer votre vie ?\n o: Oui\n n: Non (revenir au menu combat)\n");
                    while(c != 'o' && c != 'n'){
                        scanf("%s", &c);
                    }
                    if(c == 'o'){
                        if(player.inventory[i].id == 2){
                            player.hp += 5;
                            player.inventory[i].id = NO_ITEM_ID;
                            strcpy(player.inventory[i].name, "");
                        }
                        else if(player.inventory[i].id == 4){
                            player.hp += 10;
                            player.inventory[i].id = NO_ITEM_ID;
                            strcpy(player.inventory[i].name, "");
                        }
                    }
                    else if(c == 'n'){
                        system("clear");
                        printf("Vous revenez au menu combat\n\n");
                    }
                }
            }
        }
        else if(c == '3'){
            printf("Fuir le duel vous enlève 5 pv, êtes-vous sur de vouloir faire ça ?\n o: oui\n n: Non (revenir au menu combat)\n");
            while(c != 'o' && c != 'n'){
                scanf("%s", &c);
            }
            if(c == 'o'){
                system("clear");
                mob.hp = 0;
                player.hp -= 5;
            }
            else if(c == 'n'){
                printf("Vous revenez au menu combat\n\n");
            }
        }
    }
    
}

Mob getMob(int id){
    return mobs[id];
}

Mob setMob(int id, Mob mob){
    mobs[id] = mob;
}