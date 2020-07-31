#include "cabecalhoFuncoes.h"

int main(){

    SMALL_RECT ret = {0,0,200,37};
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE),TRUE,&ret); //tamanho da janela
    srand(time(NULL));
    int opt;
    velocidade = NORMAL;
    inicio_do_jogo = TRUE;
    criarFicheiros();

    while(TRUE){
        opt = menu();
        inicio_do_jogo = FALSE;
        switch(opt){
            case 1: iniciarJogo(); break;
            case 2: dificuldade(); break;
            case 3: recordes(); break;
            case 4: ajuda(); break;
            case 5: sair(); break;
            default: system("pause");
        }
    }
}


