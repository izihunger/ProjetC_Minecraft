# include <stdio.h>
# include <stdlib.h>

// Structure : START
typedef struct Bloc
{
    char display;
    int crossable;
    int spawnable;
    int breakable;
    Item item;
}Bloc;

typedef struct Item
{
    char display;
}Item;
// Structure : END

const Item i_dirt = {'d'};
const Item i_stone = {'d'};
const Item i_ = {'d'};

const Bloc Dirt = {'d', 1, 1, 1};
const Bloc Stone = {'s', 1, 1, 1};
const Bloc Tree = {'t', 0, 1, 0};
const Bloc Water = {'w', 1, 1, 1};


// Function to create the menu : START
int displayMenu(){
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

void displayMap(Bloc ** map, int size){
    system("cls");
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            printf("%c ", map[i][j].display);
        }
        printf("\n");
    }
}

int main(){
    Bloc ** map = NULL;
    int value = menu();
    if(value == 1){
        int size;
        printf("Entrez la taille de votre map(cette valeur definira la largeur et la longueur de la map) : ");
        scanf("%d", &size);
        map = generateMap(size);
        showMap(map, size);
        /*fflush(stdout);
        char c = _getch();
        printf("%c", c);*/
    }
    else if(value == 2){
        //TODO
        return 0;
    }
    else if(value == 3){
        return 0;
    }
    return 0;
}