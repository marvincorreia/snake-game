#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

typedef struct ponto{
    int x,y;
}PONTO;
int main(){

    srand(time(NULL));
    int xmin=10,xmax=30,ymin=5,ymax=20;
    PONTO* p = (PONTO*)malloc(sizeof(PONTO));

    while(TRUE){
        p->x = (xmin+1) + rand()%(xmax-xmin-1);
        p->y = (ymin+1) + rand()%(ymax-ymin-1);
        printf("x = %d y = %d\n",p->x,p->y);
        Sleep(500);
    }
    system("pause");
}
