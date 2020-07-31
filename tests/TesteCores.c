#include <stdio.h>
#include <windows.h>


int main(){

    int cor;
    for(cor=0;cor<300;cor++){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),cor);
        printf(" %d -> cor\n",cor);
        //Sleep(100);
    }
    system("pause");
}
