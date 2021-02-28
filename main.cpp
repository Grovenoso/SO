#if _WIN64 || _WIN32
    #define CLEAR system("cls")
    #include <Windows.h>
    #define SLEEP(x) Sleep(x);
#else
    #define CLEAR system("clear");
    #define SLEEP(x) std::this_thread::sleep_for(std::chrono::milliseconds(x));
#endif

#include <iostream>
#include <stdio.h>
#include <chrono>
#include <thread>
#include <queue>

#define GOTOXY(x, y) printf("%c[%d;%df",0x1B,y,x);
#define HIDECURSOR printf("\e[?25l");
#define SHOWCURSOR printf("\e[?25h");

#include "programmer.h"

int main()
{
    int a;   
    CLEAR; //limpia la pantalla
    HIDECURSOR; //esconde el cursor
    for(int i(0); i<3; ++i) {
        GOTOXY(0,0); //modifica la posición
        SLEEP(1000); //tiempo de espera (en milisegundos)
        std::cout<<i<<std::endl;
    }
    SHOWCURSOR; //muestra el cursor otra vez
    std::cin>>a;
}