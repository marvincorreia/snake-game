#include <stdio.h>
#include <locale.h>

int main(){

    printf("Idioma: %s\n",setlocale(LC_ALL,NULL));
    printf("Acentua��o\n");

    printf("\nIdioma: %s\n",setlocale(LC_ALL,""));
    printf("Acentua��o\n\n");
    system("pause");
}
