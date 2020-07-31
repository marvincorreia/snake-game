#ifndef CABECALHOFUNCOES_H_INCLUDED
#define CABECALHOFUNCOES_H_INCLUDED

//VERSÃO
#define VERSION 3

//BIBLIOTECAS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <locale.h>
#include <pthread.h>
#include <time.h>
#include <string.h>

//CONSTANTES
#define XINIT 11
#define YINIT 7
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ENTER 13
#define FACIL 150
#define NORMAL 100
#define DIFICIL 50
#define EXPERT 30
#define BACK_GROUND 20
#define VERDE 10
#define BLACK 0
#define AZUL 11
#define VERMELHO 12
#define AMARELO 14
#define AZ_VERDE 26
#define AZ_AZUL 27
#define AZ_VERMELHO 28
#define AZ_AMARELO 30
#define AZ_BRANCO 31
#define FICH_FACIL "score_facil.txt"
#define FICH_NORMAL "score_normal.txt"
#define FICH_DIFICIL "score_dificil.txt"
#define FICH_EXPERT "score_expert.txt"
#define POWERBYDELAY 3


//ESTRUTURA DE DADOS (LISTA DUPLAMENTE LIGADA)
typedef struct node{
    char item;
    int x,y;
    struct node* proximo;
    struct node* anterior;
}NODE;

typedef struct jogador{
    char* nome;
    int pontuacao;
}PLAYER;

typedef struct time{
    int horas, minutos, segundos;
}TIMER;

//VARIAVEIS GLOBAIS
NODE* listaSnake;
NODE* head;
NODE* headAnterior;
NODE* tail;
NODE* semente;
PLAYER* player;
TIMER* timer;
int totalNodes, xSnake, ySnake, xSemente, ySemente, velocidade, pontos;
int quadroXmin, quadroYmin, quadroXmax, quadroYmax;
int power_by_counter;
char direcao;
pthread_t thread_inputDirecao, thread_autoMover, thread_validacao,thread_publicidade, thread_temporizador;
BOOL valido, inicio_do_jogo, display_power_by;


//POSICIONAR CURSOR
void gotoxy(int x,int y);

//CONTROLE
void moverDireita();
void moverEsquerda();
void moverBaixo();
void moverCima();

//ATUALIZADORES
void atualizarCoordenada();
void limparRasto(int speed);
void atualizarDisplay();

//THEADS FUNCTIONS
void* inputDirecao();
void* autoMover();
void* validacao();
void* temporizador();

//POWER BY METHODS
void showPowerBy();
void changePowerByFlag();
void resetPowerByCounter();

//METODOS DIVERSOS
void criarQuadro(int delay, int tipo, int backGround);
int menu();
void cabecalho_do_menu();
void sair();
void iniciarJogo();
void receberJogador();
NODE* gerarSemente();
void mostrarSemente();
void info();
void mudarCor(int cor);
void animacaoGameOver();
void comer();
void dificuldade();
void ajuda();
void recordes();
void resetarPontuacao();
void criarFicheiros();
void verTabelas();
void tabelaFacil();
void tabelaNormal();
void tabelaDificil();
void tabelaExpert();
void gravarPontuacao();
int contarLinhas(FILE* f);

// METODOS DE ORDENACÃO
void swap(PLAYER* x, PLAYER* y);
void selectionSort(PLAYER a[], int l, int r);

//METODOS LISTA  DUPLAMENTE LIGADA
int vazia(NODE* lista);
NODE* alocaNO();
void iniciaLista(NODE* lista);
NODE* novoNO();
void inserirNaLista(NODE* lista);
void exibirLista(NODE* lista);
void liberaLista(NODE* lista);

#endif // CABECALHOFUNCOES_H_INCLUDED
