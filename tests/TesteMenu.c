#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <pthread.h>


//CONSTANTES
#define XINIT 10;
#define YINIT 10;
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ENTER 13

typedef struct node{
    char item;
    int x,y;
    struct node* prox;
    struct node* ant;
}NODE;

void gotoxy(int x,int y){
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

int menu(){
    int c,x=18,y=11,opt=1;

    gotoxy(32,4);  printf("%c%c%c",219,219,219);
    gotoxy(20,5);  printf("SNAKE GAME    %c%c%c%c",219,219,219,219);
    gotoxy(37,6);  printf("%c%c%c %c",219,219,219,219);
    gotoxy(27,8);  printf("MENU");
    gotoxy(20,11); printf("Iniciar Jogo");
    gotoxy(20,13); printf("Escolher Dificuldade");
    gotoxy(20,15); printf("Recordes");
    gotoxy(20,17); printf("Ajuda");
    gotoxy(20,19); printf("Sair");
    gotoxy(x,y);   printf("%c",175);

    while(TRUE){
        c=getch();
        if(c>100)
            continue;
        if(c==ENTER)
            break;
        if(c==UP){
            if(opt!=1){
                opt--;
                gotoxy(x,y); printf(" ");
                y-=2;
                gotoxy(x,y); printf("%c",175);
            }
        }
        if(c==DOWN){
            if(opt!=5){
                opt++;
                gotoxy(x,y); printf(" ");
                y+=2;
                gotoxy(x,y); printf("%c",175);
            }
        }
    }
    return opt;
}

int main(){

   int opt = menu();
   gotoxy(0,25);
   printf("\n%d\n",opt);
   system("pause");
   return 0;
}
