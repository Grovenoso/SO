#if _WIN64 || _WIN32
    #define CLEAR system("cls")
    #include <Windows.h>
    #define SLEEP(x) Sleep(x);
#else
    #define CLEAR system("clear");
    #define SLEEP(x) std::this_thread::sleep_for(std::chrono::milliseconds(x));
#endif

#define GOTOXY(x, y) printf("%c[%d;%df",0x1B,y,x);
#define HIDECURSOR printf("\e[?25l");
#define SHOWCURSOR printf("\e[?25h");

#include <iostream>
#include <stdio.h>
#include <chrono>
#include <thread>
#include <queue>

#include "programmer.h"

using namespace std;

void programmerEntry(queue<programmer> programmerQueue)
{
    bool option;
    programmer* temporalProgrammer;
    string data;

    do{
        cout<<"Bienvenido, si desea ingresar un nuevo programa ingrese el numero 1, de lo contrario, ingrese 0" << endl;
        cin>>option;
        if(option){
            temporalProgrammer = new programmer();
            cout << "Ingrese el nombre del programador: ";
            cin >> data;
            temporalProgrammer -> setName(data);
            
        }
    }while(option);
}

int main()
{
    queue <programmer> programmerQueue;
    int a;   
    CLEAR; //limpia la pantalla
    HIDECURSOR; //esconde el cursor
    for(int i(0); i<3; ++i) {
        GOTOXY(0,0); //modifica la posición
        SLEEP(1000); //tiempo de espera (en milisegundos)
        cout<<i<<std::endl;
    }
    SHOWCURSOR; //muestra el cursor otra vez
    cin>>a;
}