# include <stdio.h>
# include <stdlib.h>

// Structure : START
typedef struct Bloc
{
    char display;
    int crossable;
    int drop;
    int spawnable;
}Bloc;
// Structure : END

// Function to create the menu : START
int menu(){
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
// Function to create the menu : END

// Function to generate the map : START
Bloc** createGrid(int size){
    Bloc ** map = (Bloc**) malloc(size * sizeof(Bloc*));
    for (int i = 0; i < size; i++)
    {
        map[i] = (Bloc*) malloc(size * sizeof(Bloc));
    }
    return map;
}

Bloc** generateMap(int size){
    Bloc ** map = createGrid(size);
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            map[i][j].display = 'd';
        }
    }
    return map;
}
// Function to generate the map : END

void showMap(Bloc ** map, int size){
    system("cls");
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            printf("%c ", map[i][j].display);
        }
        printf("\n");
    }
}

int main(){
    int size;
    printf("Entrez la taille de votre map(cette valeur definira la largeur et la longueur de la map) : ");
    scanf("%d", &size);
    Bloc ** map = generateMap(size);
    showMap(map, size);
    /*fflush(stdout);
    char c = _getch();
    printf("%c", c);*/
    return 0;
}