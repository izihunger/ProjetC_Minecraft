#ifndef ITEM_H
#define ITEM_H

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

Item selectItem(int value);

#endif