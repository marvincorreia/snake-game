#include "cabecalhoFuncoes.h"

//METODOS LISTA Duplamente Ligada-------------------------------------------------------------------
NODE* alocaNO(){
    NODE* no = (NODE*) malloc(sizeof(NODE));
    return no;
}


int vazia(NODE* lista){
    return lista->proximo == NULL;
}


void iniciaLista(NODE* lista){
    lista->proximo = NULL;
    lista->anterior = NULL;
}


NODE* novoNO(){
    NODE* novo = alocaNO();
    novo->item = 184;  //  © (copyright) ascii code
    novo->proximo = NULL;
    return novo;
}


void inserirNaLista(NODE* lista){
    NODE* novo = novoNO();
    if(vazia(lista)){
        lista->proximo = novo;
        tail = novo;
        totalNodes++;
    }else{
        NODE* aux = lista->proximo;
        while(aux->proximo != NULL){
            aux = aux->proximo;
        }
        novo->anterior = aux;
        aux->proximo = novo;
        novo->x = headAnterior->x;
        novo->y = headAnterior->y;
        tail = novo;
        totalNodes++;
    }
}


void exibirLista(NODE* lista){
    NODE* aux = lista->proximo;
    mudarCor(AZ_VERDE);
    if(aux == NULL)
        printf("Lista vazia!\n");
    else{
        while(aux != NULL){
            if(aux == head){ // O node head tem cor branco
                mudarCor(AZ_BRANCO);
                gotoxy(aux->x,aux->y);
                printf("%c",aux->item);
                mudarCor(AZ_VERDE);
            }else{
                gotoxy(aux->x,aux->y);
                printf("%c",aux->item);
            }
            aux=aux->proximo;
        }
    }
}


void liberaLista(NODE* lista){
	if(!vazia(lista)){
		NODE* proximoNo;
		NODE* atual;
		atual = lista->proximo;
		while(atual != NULL){
			proximoNo = atual->proximo;
			free(atual);
			atual = proximoNo;
		}
	}
}


//METODOS DE MUDANCA DE DIRECAO---------------------------------------------------------------

// Posicionar cursor
void gotoxy(int x,int y){
    COORD coordenada;
    coordenada.X = x;
    coordenada.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coordenada);
}

void moverDireita(){
    headAnterior->x=xSnake;
    headAnterior->y=ySnake;
    xSnake++;
    head->x=xSnake;
    head->y=ySnake;
}

void moverEsquerda(){
    headAnterior->x=xSnake;
    headAnterior->y=ySnake;
    xSnake--;
    head->x=xSnake;
    head->y=ySnake;
}

void moverBaixo(){
    headAnterior->x=xSnake;
    headAnterior->y=ySnake;
    ySnake++;
    head->x=xSnake;
    head->y=ySnake;
}

void moverCima(){
    headAnterior->x=xSnake;
    headAnterior->y=ySnake;
    ySnake--;
    head->x=xSnake;
    head->y=ySnake;
}


// ATUALIZADORES ------------------------------------------------------------------------
void limparRasto(int speed){
    Sleep(speed/20);
    mudarCor(BACK_GROUND);
    gotoxy(tail->x,tail->y);
    printf(" ");
}

void atualizarCoordenada(){
    NODE* aux1 = tail;
    if(head->proximo != NULL){
        while(aux1->anterior != head){
            aux1=aux1->anterior;
            aux1->proximo->x = aux1->x;
            aux1->proximo->y = aux1->y;
        }
        head->proximo->x=headAnterior->x;
        head->proximo->y=headAnterior->y;
    }
}

void atualizarDisplay(){
    atualizarCoordenada();
    exibirLista(listaSnake);
    comer();
    mostrarSemente(semente);
    info();
    showPowerBy();
    limparRasto(velocidade);
}


//THREADS FUNCTIONS ------------------------------------------------------------------------------------

void* validacao(){
    while(valido){
        if(head->x <= quadroXmin || head->x >= quadroXmax )
            valido = FALSE;
        else if(head->y <= quadroYmin || head->y >= quadroYmax )
            valido = FALSE;
        else{
            NODE* aux = head->proximo;
            while(aux != tail){
                if(head->x == aux->x && head->y == aux->y){
                    valido=FALSE;
                }
                aux=aux->proximo;
                Sleep(1);
            }
        }
    }
}

void* autoMover(){
    //limparRasto(0);
    while(valido){
        switch(direcao){
            case UP: moverCima();  break;
            case DOWN: moverBaixo(); break;
            case LEFT : moverEsquerda();   break;
            case RIGHT : moverDireita();  break;
            default : continue;
        }
        atualizarDisplay();
        Sleep(velocidade);
    }
}

void* inputDirecao(){
    int tecla;
    while(valido){
        tecla=getch();

        if(tecla!=UP && tecla!=DOWN && tecla!=LEFT && tecla!=RIGHT)
            continue;
        if( (direcao==UP && tecla==DOWN) || (direcao==DOWN && tecla==UP))
            continue;
        if( (direcao==RIGHT && tecla==LEFT) || (direcao==LEFT && tecla==RIGHT))
            continue;

        direcao=tecla;
        Sleep(velocidade+25);
    }
}


void* temporizador(){
    while(valido){
        Sleep(1000);
        timer->segundos++;
        power_by_counter++;
        resetPowerByCounter();
        if(timer->segundos>59){
            timer->segundos = 0;
            timer->minutos++;
            if(timer->minutos > 59){
                timer->minutos = 0;
                timer->horas++;
            }
        }
    }
}



//METODOS ------------------------------------------------------------------------------------

void comer(){
    if(head->x == semente->x && head->y == semente->y){
        inserirNaLista(listaSnake);
        pontos++;
        semente = gerarSemente();
    }
}

void showPowerBy(){
    int x=31, y=35;

    if(display_power_by){
        mudarCor(VERDE);
        gotoxy(x,y); printf("<< POWER BY MARVIN CORREIA >>");
    }else{
        mudarCor(BLACK);
        gotoxy(x,y); printf("\t\t\t\t\t");
    }
}

void changePowerByFlag(){
    if(display_power_by){
        display_power_by = FALSE;
    }else{
        display_power_by = TRUE;
    }
}

void resetPowerByCounter(){
    if(power_by_counter >= POWERBYDELAY){
        power_by_counter = 0;
        changePowerByFlag();
    }
}

void info(){
    mudarCor(AMARELO);
    gotoxy(10,1); printf("I N F O");
    gotoxy(10,3); printf("Pontos >> %d",pontos);
    gotoxy(25,3); printf("Speed >> %d",230-velocidade);
    if(velocidade==FACIL){
        gotoxy(40,3); printf("Dificuldade >> Facil");
    }else if(velocidade==NORMAL){
        gotoxy(40,3); printf("Dificuldade >> Normal");
    }else if(velocidade==DIFICIL){
        gotoxy(40,3); printf("Dificuldade >> Dificil");
    }else if(velocidade==EXPERT){
        gotoxy(40,3); printf("Dificuldade >> Expert");
    }

    gotoxy(10,32); printf("cabeca  >> X=%d Y=%d",head->x,head->y);
    gotoxy(10,33); printf("cauda   >> X=%d Y=%d\t\t\t",tail->x,tail->y);
    gotoxy(10,34); printf("semente >> X=%d Y=%d",semente->x,semente->y);
    gotoxy(58,32); printf("tempo >> %dh : %dm : %ds  ",timer->horas, timer->minutos, timer->segundos);
}


void criarQuadro(int delay, int tipo, int backGround){
    int i;
    quadroXmin=9; quadroYmin=5;
    quadroXmax=80; quadroYmax=30;

    setlocale(LC_ALL,"C");
    mudarCor(VERMELHO);

    // criar borda
    for(i=quadroXmin;i<quadroXmax;i++){
        gotoxy(i,quadroYmin);
        printf("%c",tipo);
        Sleep(delay);
    }
    for(i=quadroYmin;i<quadroYmax;i++){
        gotoxy(quadroXmax,i);
        printf("%c",tipo);
        Sleep(delay);
    }
    for(i=quadroXmax;i>quadroXmin;i--){
        gotoxy(i,quadroYmax);
        printf("%c",tipo);
        Sleep(delay);
    }
    for(i=quadroYmax;i>quadroYmin;i--){
        gotoxy(quadroXmin,i);
        printf("%c",tipo);
        Sleep(delay);
    }

    mudarCor(backGround);

    //preencher quadro linha a linha
    int largura_interna = quadroXmax - quadroXmin - 1;
    char* linha_de_prenchimento = calloc(largura_interna,sizeof(char));
    for(i=0;i<largura_interna;i++){
        linha_de_prenchimento[i] = ' ';
    }
    linha_de_prenchimento[i] = ' \0';
    for(i=quadroYmin+1;i<quadroYmax;i++){
        gotoxy(quadroXmin+1,i);
        printf("%s",linha_de_prenchimento);
        //Sleep(0);
    }
}


void iniciarJogo(){
    player = (PLAYER*)malloc(sizeof(PLAYER));
    receberJogador();

    timer = (TIMER*) malloc(sizeof(TIMER));
    pontos=0, timer->segundos=0, timer->minutos=0, timer->horas=0, power_by_counter=0;
    listaSnake = alocaNO();
    headAnterior = alocaNO();
    iniciaLista(listaSnake);
    inserirNaLista(listaSnake); //Inserir Head
    inserirNaLista(listaSnake); //Inserir Tail
    head = listaSnake->proximo;
    xSnake = XINIT, ySnake = YINIT;
    head->x = xSnake, head->y = ySnake;
    semente = gerarSemente();

    mudarCor(BLACK);
    system("cls");
    criarQuadro(0,219,BACK_GROUND);
    info();
    gotoxy(head->x,head->y);
    printf("%c",head->item);
    gotoxy(0,35);

    while(direcao!=UP && direcao!=DOWN && direcao!=LEFT && direcao!=RIGHT){
        direcao=getch();
    }

    valido = TRUE;

    pthread_create(&thread_inputDirecao,NULL,inputDirecao,NULL);
    pthread_create(&thread_autoMover,NULL,autoMover,NULL);
    pthread_create(&thread_validacao,NULL,validacao,NULL);
    pthread_create(&thread_temporizador,NULL,temporizador,NULL);

    //ciclo principal do jogo
    while(valido){

    }

    pthread_cancel(thread_inputDirecao);
    pthread_cancel(thread_autoMover);
    pthread_cancel(thread_validacao);
    pthread_cancel(thread_temporizador);
    Sleep(100);
    animacaoGameOver();
    player->pontuacao = pontos;
    gravarPontuacao();
    direcao=0;
    liberaLista(listaSnake);
    totalNodes=0;
    system("cls");
}


void receberJogador(){
    char nome[30];
    int delay=400;

    INICIO:
    cabecalho_do_menu();
    gotoxy(37,12);  printf("J O G A D O R"); Sleep(delay);
    mudarCor(AZ_VERMELHO);
    gotoxy(29,26); printf("OBS : Nome não deve conter espaços");
    mudarCor(AZ_AZUL);
    gotoxy(25,16);  printf("Inserir nome -> ");
    mudarCor(AZ_AMARELO);
    gets(nome);
    if(strcmp(nome,"")==0){
        mudarCor(AZ_VERMELHO);
        gotoxy(29,24); printf("Nome não pode ser vazio!"); Sleep(delay);
        getch();
        goto INICIO;
    }

    player->nome=strdup(nome);
    setlocale(LC_ALL,"C");
}


void animacaoGameOver(){
    int i,x,y,input;
    mudarCor(VERMELHO);
    for(i=0;i<1000;i++){
        x = (quadroXmin+1) + rand()%(quadroXmax-quadroXmin-1);
        y = (quadroYmin+1) + rand()%(quadroYmax-quadroYmin-1);
        gotoxy(x,y);
        printf("%c",178);
        gotoxy(quadroXmax/2-15,quadroYmax/2+1);
        printf("\t\t\t\t\t");
        gotoxy(quadroXmax/2-10,quadroYmax/2+2);
        printf("       G A M E  O V E R        ");
        gotoxy(quadroXmax/2-15,quadroYmax/2+3);
        printf("\t\t\t\t\t");
        //Sleep(1);
    }

    gotoxy(10,37);
    printf("Prima ENTER para retornar ao menu...");
    while(input!=ENTER){
        input = getch();
    }
}

void cabecalho_do_menu(){
    mudarCor(0);
    system("cls");
    criarQuadro(0,178,BACK_GROUND);
    setlocale(LC_ALL,"Portuguese");
    mudarCor(AZ_VERDE);
    gotoxy(33,7);  printf("  S N A K E  G A M E ");
    gotoxy(39,9);  printf("%c%c%c%c%c%c%c %c",169,169,169,169,169,169,169,169);
    mudarCor(AZ_AMARELO);

}

int menu(){
    int input,x=30,y=15,opt=1,delay=0;

    if (inicio_do_jogo)
        delay = 100;

    cabecalho_do_menu();
    gotoxy(40,12);  printf("M E N U");  Sleep(delay);
    mudarCor(AZ_AZUL); Sleep(delay);
    gotoxy(33,15); printf("Iniciar Jogo"); Sleep(delay);
    gotoxy(33,17); printf("Escolher Dificuldade"); Sleep(delay);
    gotoxy(33,19); printf("Recordes"); Sleep(delay);
    gotoxy(33,21); printf("Ajuda"); Sleep(delay);
    gotoxy(33,23); printf("Sair"); Sleep(delay);
    mudarCor(AZ_VERMELHO);
    gotoxy(33,26); printf("Navegação: Setas cima,baixo ");
    gotoxy(33,27); printf("Seleção: Prima ENTER ");
    mudarCor(AZ_AMARELO);
    gotoxy(x,y);   printf("%c",187);
    gotoxy(15,32);

    while(TRUE){
        mudarCor(0);
        input=getch();
        mudarCor(AZ_AMARELO);
        if(input>100)
            continue;
        if(input==ENTER)
            break;
        if(input==UP){
            if(opt!=1){
                opt--;
                gotoxy(x,y); printf(" ");
                y-=2;
                gotoxy(x,y); printf("%c",187);
                gotoxy(15,32);
            }
        }
        if(input==DOWN){
            if(opt!=5){
                opt++;
                gotoxy(x,y); printf(" ");
                y+=2;
                gotoxy(x,y); printf("%c",187);
                gotoxy(15,32);
            }
        }
    }
    setlocale(LC_ALL,"C");
    return opt;
}


void recordes(){
    int c,x=30,y=15,opt=1,vel=0;

    cabecalho_do_menu();
    gotoxy(33,12);  printf("S C O R E  B O A R D");  Sleep(vel);
    mudarCor(AZ_AZUL);
    gotoxy(33,15);  printf("Ver pontuações");  Sleep(vel);
    gotoxy(33,17);  printf("Resetar pontuações");  Sleep(vel);
    gotoxy(33,19);  printf("Retornar ao MENU");  Sleep(vel);
    mudarCor(AZ_VERMELHO);
    gotoxy(33,26); printf("Navegação: Setas cima,baixo "); Sleep(vel);
    gotoxy(33,27); printf("Seleção: Prima ENTER "); Sleep(vel*2);
    mudarCor(AZ_AMARELO);
    gotoxy(x,y);   printf("%c",187);
    gotoxy(15,32);

    while(TRUE){
        mudarCor(0);
        c=getch();
        mudarCor(AZ_AMARELO);
        if(c>100)
            continue;
        if(c==ENTER)
            break;
        if(c==UP){
            if(opt!=1){
                opt--;
                gotoxy(x,y); printf(" ");
                y-=2;
                gotoxy(x,y); printf("%c",187);
                gotoxy(15,32);
            }
        }
        if(c==DOWN){
            if(opt!=3){
                opt++;
                gotoxy(x,y); printf(" ");
                y+=2;
                gotoxy(x,y); printf("%c",187);
                gotoxy(15,32);
            }
        }
    }

    switch(opt){
        case 1: verTabelas(); break;
        case 2: resetarPontuacao(); break;
        case 3: break;
    }

    setlocale(LC_ALL,"C");
}


void verTabelas(){
    int c,opt=0,vel=0;

    cabecalho_do_menu();
    mudarCor(AZ_AMARELO);
    gotoxy(33,12);  printf("S C O R E  B O A R D");  Sleep(vel);
    mudarCor(AZ_AZUL);
    gotoxy(33,15);  printf("Utilize as setas esq e dir");  Sleep(vel);
    gotoxy(33,17);  printf("para ver as pontuações!");  Sleep(vel);
    mudarCor(AZ_VERMELHO);
    gotoxy(33,26); printf("Navegação: Setas esquerda,direita "); Sleep(vel);
    gotoxy(33,27); printf("Prima ENTER para sair... "); Sleep(vel*2);
    gotoxy(15,32);
    mudarCor(AZ_AMARELO);
    gotoxy(68,16);  printf("%c",187);
    gotoxy(21,16);  printf("%c",171);
    gotoxy(15,32);

    while(TRUE){
        mudarCor(0);
        c=getch();
        mudarCor(AZ_AMARELO);
        CONTINUACAO:
        if(c>100)
            continue;
        if(c==ENTER)
            break;
        if(c==LEFT){
            if(opt!=1 && opt!=0){
                opt--;
                switch(opt){
                    case 1: tabelaFacil(); break;
                    case 2: tabelaNormal(); break;
                    case 3: tabelaDificil(); break;
                    case 4: tabelaExpert(); break;
                }
                gotoxy(15,32);
                c=getch();
                goto CONTINUACAO;
            }
        }
        if(c==RIGHT){
            if(opt!=4){
                opt++;
                switch(opt){
                    case 1: tabelaFacil(); break;
                    case 2: tabelaNormal(); break;
                    case 3: tabelaDificil(); break;
                    case 4: tabelaExpert(); break;
                }
                gotoxy(15,32);
                c=getch();
                goto CONTINUACAO;
            }
        }
    }
}


void tabelaFacil(){
    int i,x1=33,x2=48,y=19,vel=0,linhas;
    PLAYER* jogadores;
    FILE* f = fopen(FICH_FACIL,"r");
    char nomeAux[30];

    cabecalho_do_menu();
    gotoxy(39,12);  printf("F A C I L");  Sleep(vel);
    mudarCor(AZ_AZUL);
    linhas=contarLinhas(f);
    gotoxy(30,15);  printf("Top 4 Jogadores de %d jogos",linhas);  Sleep(vel);
    gotoxy(33,17);  printf("Nome");  Sleep(vel);
    gotoxy(48,17);  printf("Pontos");  Sleep(vel);
    mudarCor(AZ_VERMELHO);
    gotoxy(33,28); printf("Prima ENTER para sair... "); Sleep(vel);
    mudarCor(AZ_AMARELO);
    gotoxy(68,18);  printf("%c",187);

    if(linhas==0){
        mudarCor(AZ_VERMELHO);
        gotoxy(33,23); printf("Sem recordes ainda!"); Sleep(vel);
        fclose(f);
        gotoxy(15,32);
    }
    else{
        jogadores=(PLAYER*)malloc(linhas*sizeof(PLAYER));
        for(i=0;i<linhas;i++){
            fscanf(f,"%s %d",nomeAux,&jogadores[i].pontuacao);
            jogadores[i].nome = strdup(nomeAux);
        }
        fclose(f);
        selectionSort(jogadores,0,linhas-1);
        for(i=0;i<linhas;i++,y+=2){
            if(i==4)
                break;
            gotoxy(x1-3,y); printf("%d",i+1);
            gotoxy(x1,y);  printf("%s",jogadores[i].nome);
            gotoxy(x2,y);  printf("%d",jogadores[i].pontuacao);
        }
    }
}


void tabelaNormal(){
    int i,x1=33,x2=48,y=19,vel=0,linhas;
    PLAYER* jogadores;
    FILE* f = fopen(FICH_NORMAL,"r");
    char nomeAux[30];

    cabecalho_do_menu();
    gotoxy(38,12);  printf("N O R M A L");  Sleep(vel);
    mudarCor(AZ_AZUL);
    linhas=contarLinhas(f);
    gotoxy(30,15);  printf("Top 4 Jogadores de %d jogos",linhas);  Sleep(vel);
    gotoxy(33,17);  printf("Nome");  Sleep(vel);
    gotoxy(48,17);  printf("Pontos");  Sleep(vel);
    mudarCor(AZ_VERMELHO);
    gotoxy(33,28); printf("Prima ENTER para sair... "); Sleep(vel);
    mudarCor(AZ_AMARELO);
    gotoxy(20,18);  printf("%c",171);
    gotoxy(68,18);  printf("%c",187);

    if(linhas==0){
        mudarCor(AZ_VERMELHO);
        gotoxy(33,23); printf("Sem recordes ainda!"); Sleep(vel);
        fclose(f);
        gotoxy(15,32);
    }
    else{
        jogadores=(PLAYER*)malloc(linhas*sizeof(PLAYER));
        for(i=0;i<linhas;i++){
            fscanf(f,"%s %d",nomeAux,&jogadores[i].pontuacao);
            jogadores[i].nome = strdup(nomeAux);
        }
        fclose(f);
        selectionSort(jogadores,0,linhas-1);
        for(i=0;i<linhas;i++,y+=2){
            if(i==4)
                break;
            gotoxy(x1-3,y); printf("%d",i+1);
            gotoxy(x1,y);  printf("%s",jogadores[i].nome);
            gotoxy(x2,y);  printf("%d",jogadores[i].pontuacao);
        }
    }
}


void tabelaDificil(){
    int i,x1=33,x2=48,y=19,vel=0,linhas;
    PLAYER* jogadores;
    FILE* f = fopen(FICH_DIFICIL,"r");
    char nomeAux[30];

    cabecalho_do_menu();
    gotoxy(37,12);  printf("D I F I C I L");  Sleep(vel);
    mudarCor(AZ_AZUL);
    linhas=contarLinhas(f);
    gotoxy(30,15);  printf("Top 4 Jogadores de %d jogos",linhas);  Sleep(vel);
    gotoxy(33,17);  printf("Nome");  Sleep(vel);
    gotoxy(48,17);  printf("Pontos");  Sleep(vel);
    mudarCor(AZ_VERMELHO);
    gotoxy(33,28); printf("Prima ENTER para sair... "); Sleep(vel);
    mudarCor(AZ_AMARELO);
    gotoxy(20,18);  printf("%c",171);
    gotoxy(68,18);  printf("%c",187);

    if(linhas==0){
        mudarCor(AZ_VERMELHO);
        gotoxy(33,23); printf("Sem recordes ainda!"); Sleep(vel);
        fclose(f);
        gotoxy(15,32);
    }
    else{
        jogadores=(PLAYER*)malloc(linhas*sizeof(PLAYER));
        for(i=0;i<linhas;i++){
            fscanf(f,"%s %d",nomeAux,&jogadores[i].pontuacao);
            jogadores[i].nome = strdup(nomeAux);
        }
        fclose(f);
        selectionSort(jogadores,0,linhas-1);
        for(i=0;i<linhas;i++,y+=2){
            if(i==4)
                break;
            gotoxy(x1-3,y); printf("%d",i+1);
            gotoxy(x1,y);  printf("%s",jogadores[i].nome);
            gotoxy(x2,y);  printf("%d",jogadores[i].pontuacao);
        }
    }
}


void tabelaExpert(){
int i,x1=33,x2=48,y=19,delay=0,linhas;
    PLAYER* jogadores;
    FILE* f = fopen(FICH_EXPERT,"r");
    char nomeAux[30];

    cabecalho_do_menu();
    gotoxy(37,12);  printf("E X P E R T");  Sleep(delay);
    mudarCor(AZ_AZUL);
    linhas=contarLinhas(f);
    gotoxy(30,15);  printf("Top 4 Jogadores de %d jogos",linhas);  Sleep(delay);
    gotoxy(33,17);  printf("Nome");  Sleep(delay);
    gotoxy(48,17);  printf("Pontos");  Sleep(delay);
    mudarCor(AZ_VERMELHO);
    gotoxy(33,28); printf("Prima ENTER para sair... "); Sleep(delay);
    mudarCor(AZ_AMARELO);
    gotoxy(20,18);  printf("%c",171);

    if(linhas==0){
        mudarCor(AZ_VERMELHO);
        gotoxy(33,23); printf("Sem recordes ainda!"); Sleep(delay);
        fclose(f);
        gotoxy(15,32);
    }
    else{
        jogadores=(PLAYER*)malloc(linhas*sizeof(PLAYER));
        for(i=0;i<linhas;i++){
            fscanf(f,"%s %d",nomeAux,&jogadores[i].pontuacao);
            jogadores[i].nome = strdup(nomeAux);
        }
        fclose(f);
        selectionSort(jogadores,0,linhas-1);
        for(i=0;i<linhas;i++,y+=2){
            if(i==4)
                break;
            gotoxy(x1-3,y); printf("%d",i+1);
            gotoxy(x1,y);  printf("%s",jogadores[i].nome);
            gotoxy(x2,y);  printf("%d",jogadores[i].pontuacao);
        }
    }
}


void resetarPontuacao(){
    FILE* f;
    f=fopen(FICH_FACIL,"w+"); fclose(f);
    f=fopen(FICH_NORMAL,"w+"); fclose(f);
    f=fopen(FICH_DIFICIL,"w+"); fclose(f);
    f=fopen(FICH_EXPERT,"w+"); fclose(f);

    cabecalho_do_menu();
    gotoxy(33,12);  printf("S C O R E  B O A R D");
    mudarCor(AZ_AZUL);
    gotoxy(27,15); printf("Registro de pontuações apagadas!");
    mudarCor(AZ_VERDE);
    gotoxy(37,19); printf("S U C C E S S");
    mudarCor(AZ_VERMELHO);
    gotoxy(19,27); printf("Pressione qualquer tecla para retornar ao MENU...");
    gotoxy(15,32);
    getch();
}


void criarFicheiros(){
    FILE* f;
    f=fopen(FICH_FACIL,"a"); fclose(f);
    f=fopen(FICH_NORMAL,"a"); fclose(f);
    f=fopen(FICH_DIFICIL,"a"); fclose(f);
    f=fopen(FICH_EXPERT,"a"); fclose(f);
}


void dificuldade(){

    int c,x=30,y=0,opt=1,delay=1;

    if(velocidade==EXPERT){
        y=15; opt=1;
    }
    else if(velocidade==DIFICIL){
        y=17; opt=2;
    }
    else if(velocidade==NORMAL){
        y=19; opt=3;
    }
    else if(velocidade==FACIL){
        y=21; opt=4;
    }

    cabecalho_do_menu();
    gotoxy(33,12);  printf("D I F I C U L D A D E"); Sleep(delay);
    mudarCor(AZ_AZUL);
    gotoxy(33,15); printf("Expert"); Sleep(delay);
    gotoxy(33,17); printf("Dificil"); Sleep(delay);
    gotoxy(33,19); printf("Normal"); Sleep(delay);
    gotoxy(33,21); printf("Facil"); Sleep(delay);
    mudarCor(AZ_VERMELHO);
    gotoxy(33,26); printf("Navegação: Setas cima,baixo "); Sleep(delay);
    gotoxy(33,27); printf("Seleção: Prima ENTER "); Sleep(delay);
    mudarCor(AZ_AMARELO);
    gotoxy(x,y);   printf("%c",187);
    gotoxy(15,32);

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
                gotoxy(x,y); printf("%c",187);
                gotoxy(15,32);
            }
        }
        if(c==DOWN){
            if(opt!=4){
                opt++;
                gotoxy(x,y); printf(" ");
                y+=2;
                gotoxy(x,y); printf("%c",187);
                gotoxy(15,32);
            }
        }
    }
    switch(opt){
        case 1: velocidade=EXPERT; break;
        case 2: velocidade=DIFICIL; break;
        case 3: velocidade=NORMAL; break;
        case 4: velocidade=FACIL; break;
    }
    setlocale(LC_ALL,"C");

}


void sair(){
    int delay=200;
    cabecalho_do_menu();
    gotoxy(36,13); printf("C R E D I T O S"); Sleep(delay);
    mudarCor(AZ_AZUL);
    gotoxy(30,16); printf("Jogo de Snake, versão %d.0",VERSION); Sleep(delay);
    gotoxy(30,18); printf("Powered by ");
    mudarCor(AZ_AMARELO);
    printf("MARVIN CORREIA"); Sleep(delay);
    mudarCor(AZ_AZUL);
    gotoxy(30,20); printf("CopyRight %c 2019",169);     Sleep(delay);
    gotoxy(30,22); printf("Todos os direitos de autor reservado");  Sleep(delay);
    mudarCor(AZ_VERMELHO);
    gotoxy(30,26); printf("Pressione qualquer tecla para sair..."); Sleep(delay);
    gotoxy(0,32);  getch();
    mudarCor(VERDE);
    exit(0);
}


NODE* gerarSemente(){
    NODE* semente = novoNO();
    semente->item = 'O';
    xSemente = (quadroXmin+1) + rand()%(quadroXmax-quadroXmin-1);
    ySemente = (quadroYmin+1) + rand()%(quadroYmax-quadroYmin-1);
    semente->x = xSemente;
    semente->y = ySemente;
    return semente;
}


void mostrarSemente(){
    mudarCor(AZ_AMARELO);
    gotoxy(semente->x,semente->y);
    printf("%c",semente->item);
}


void ajuda(){
    int delay=100;

    mudarCor(0);
    system("cls");
    criarQuadro(0,178,BACK_GROUND);
    setlocale(LC_ALL,"Portuguese");
    mudarCor(AZ_VERDE);
    gotoxy(33,7);  printf("  S N A K E  G A M E ");
    gotoxy(39,9);  printf("%c%c%c%c%c%c%c %c",169,169,169,169,169,169,169,169);
    mudarCor(AZ_AMARELO);
    gotoxy(39,12);  printf("A J U D A"); Sleep(delay);
    mudarCor(AZ_AZUL);
    gotoxy(17,14);  printf("O jogo consiste em pegar o maximo de sementes com a cobra,");   Sleep(delay);
    gotoxy(17,16);  printf("cada semente comida pela cobra o jogador ganha pontos e");  Sleep(delay);
    gotoxy(17,18);  printf("a cobra aumenta de tamanho, aumentando assim a dificuldade.");  Sleep(delay);
    gotoxy(17,21);  printf("Não é permitido ultrapassar a cerca \"campo de jogo\" ");   Sleep(delay);
    gotoxy(17,23);  printf("tal como não é permitido passar por cima da cobra!");   Sleep(delay);
    mudarCor(AZ_VERMELHO);
    gotoxy(19,27); printf("Pressione qualquer tecla para retornar ao MENU...");     Sleep(delay);
    gotoxy(0,32);  getch();
    setlocale(LC_ALL,"C");
}


void mudarCor(int cor){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),(WORD)cor);
}


void gravarPontuacao(){
    FILE* f;
    if (velocidade==FACIL){
        f=fopen(FICH_FACIL,"a");
        fprintf(f,"%s %d\n",player->nome,player->pontuacao);
        fclose(f);
    }
    else if (velocidade==NORMAL){
        f=fopen(FICH_NORMAL,"a");
        fprintf(f,"%s %d\n",player->nome,player->pontuacao);
        fclose(f);
    }
    else if (velocidade==DIFICIL){
        f=fopen(FICH_DIFICIL,"a");
        fprintf(f,"%s %d\n",player->nome,player->pontuacao);
        fclose(f);
    }
    else if (velocidade==EXPERT){
        f=fopen(FICH_EXPERT,"a");
        fprintf(f,"%s %d\n",player->nome,player->pontuacao);
        fclose(f);
    }
}


int contarLinhas(FILE* f){
    char c,linhas=0;
    while((c=getc(f))!=EOF){
        if(c=='\n')
            linhas++;
    }
    fseek(f,0,SEEK_SET);
    return linhas;
}


void swap(PLAYER *x,PLAYER *y){
    PLAYER temp;

    temp = *x;
    *x = *y;
    *y = temp;
}


void selectionSort(PLAYER a[], int l, int r){
    int i, j,menor;

    for (i = l; i < r; i++) {
        menor = i;
        for (j = i+1; j <= r; j++)
            if(a[j].pontuacao>a[menor].pontuacao)
                menor = j;
        swap(&a[i], &a[menor]);
    }
}





