#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <pthread.h>


void* threadFuntion(){
    while(TRUE){
        printf("Thread executando\n");
        Sleep(200);
    }
}

int main(){

    pthread_t thr;
    pthread_create(&thr,NULL,threadFuntion,NULL);
    Sleep(3000);
//    pthread_detach(thr);
    pthread_cancel(thr);
//    pthread_kill(thr,1);
    //Sleep(1000);
    printf("Thread Morreu\n");

    system("pause");
    return 0;
}

