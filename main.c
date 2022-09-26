#include <stdio.h>
#include <stdlib.h>

struct Bloc
{
    char * display;
    int crossable;
    int drop;
};


int main(){
    char c;
    while(1){
        c = getchar();
        printf("%c", c);
    }
    return 0;
}