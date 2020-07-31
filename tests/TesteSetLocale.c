#include <stdio.h>
#include <locale.h>

int main(){

    printf("Idioma: %s\n",setlocale(LC_ALL,NULL));
    printf("Acentuação\n");

    printf("\nIdioma: %s\n",setlocale(LC_ALL,""));
    printf("Acentuação\n\n");
    system("pause");
}
