#include "item.h"

const Item sword = {0, "epee"};         
const Item egg = {1, "oeuf"};       
const Item meat = {2, "viande"};  
const Item helmet = {3, "casque"};   
const Item apple = {4, "pommme"};   

const int nbItems = 5;
const int NO_ITEM_ID = 10;

// Function to select an item with his value
Item selectItem(int value){
    switch (value)
    {
        case 0:
            return sword;
        case 1:
            return egg;
        case 2:
            return meat;
        case 3:
            return helmet;
        case 4:
            return apple;
        default:
            return sword;
    }
}