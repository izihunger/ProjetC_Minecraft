#include "item.h"

const Item sword = {0, "sword"};         
const Item egg = {1, "egg"};       
const Item meal = {1, "meal"};       

Item selectItem(int value){
    switch (value)
    {
        case 0:
             return sword;
        case 1:
            return egg;
        case 2:
            return meal;
        default:
            return sword;
    }
}
