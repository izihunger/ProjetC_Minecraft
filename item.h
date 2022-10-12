#ifndef ITEM_H
#define ITEM_H
extern const int NO_ITEM_ID = 10;

#include <time.h>
#include <string.h>
#include <stdlib.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct Item
{
    int id;
    char name[255];
}Item;

extern const Item sword;         
extern const Item egg;
extern const Item meal;
extern const Item helmet;
extern const Item apple;

extern const int nbItems;

Item selectItem(int value);

#endif