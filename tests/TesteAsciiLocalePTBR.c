#include <stdio.h>
#include <locale.h>
#include <time.h>
#include <windows.h>

int main(){

    int i;
    setlocale(LC_ALL,"");
    srand(time(NULL));

//    printf("%c\n",184);
//    printf("%c\n",219);
    for(i=33;i<256;i++){
        printf("%d = %c\n",i,i);
    }
    printf("\n");
    system("pause");
}
