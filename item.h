#ifndef ITEM_H
#define ITEM_H

typedef struct Item
{
    int id;
    char name[255];
    int quantity;
    int quantityMax;
}Item;

extern const Item i_dirt;         
extern const Item i_stone;
extern const Item i_wood;

#endif