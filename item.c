#include "item.h"

const Item sword = {0, "sword"};         
const Item egg = {1, "egg"};       
const Item meal = {2, "meal"};  
const Item helmet = {3, "helmet"};   
const Item apple = {4, "apple"};   

const int nbItems = 5;

Item selectItem(int value){
    switch (value)
    {
        case 0:
             return sword;
        case 1:
            return egg;
        case 2:
            return meal;
        case 3:
            return helmet;
        case 4:
            return apple;
        default:
            return sword;
    }
}
