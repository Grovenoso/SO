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
#include <string>
#include <vector>

#include "programmer.h"

using namespace std;

void programmerEntry(vector<programmer*> programmerVector)
{
    bool option, error = true;
    programmer* temporalProgrammer;
    string data, tempData1, tempData2;
    int num1 = 0, num2 = 0;
    char operation;

    do{
        CLEAR;
        cout<<"Bienvenido, si desea ingresar un nuevo programa ingrese el numero 1, de lo contrario, ingrese 0: ";
        cin>>option;
        if(option){
            cin.ignore();
            temporalProgrammer = new programmer();
            
            cout << "Ingrese el nombre del programador: ";
            getline(cin, data);
            temporalProgrammer -> setName(data);
            
            do{
                cout << "Ingrese la operacion que desea realizar: ";
                getline(cin, data);
                
                //separacion de la operacion a terminos numericos
                if(data.find('/') < data.size()){
                    tempData1 = data.substr(0,data.find('/'));
                    tempData2 = data.substr(data.find('/') + 1, data.length());
                }

                else if (data.find('%') < data.size()){
                    tempData1 = data.substr(0, data.find('%'));
                    tempData2 = data.substr(data.find('%') + 1, data.length());
                }

                else if (data.find('+') < data.size()){
                    tempData1 = data.substr(0, data.find('+'));
                    tempData2 = data.substr(data.find('+') + 1, data.length());
                }

                else if (data.find('-') < data.size()){
                    tempData1 = data.substr(0, data.find('-'));
                    tempData2 = data.substr(data.find('-') + 1, data.length());
                }

                else if (data.find('*') < data.size()){
                    tempData1 = data.substr(0, data.find('*'));
                    tempData2 = data.substr(data.find('*') + 1, data.length());
                }

                num1 = stoi(tempData1);
                num2 = stoi(tempData2);
                
                //si la operacion es una division o residuo y el segundo (el divisor) es 0 se manda un error
                if (((data.find('/') < data.size()) || (data.find('%') < data.size())) && !num2){
                    cout << "La division entre 0 es matematicamente imposible, intente de nuevo";
                    error = true;
                    getchar();
                }

                //se realiza la operacion
                else{
                    temporalProgrammer -> setOperation(data);

                    if (data.find('/') < data.size())
                        temporalProgrammer -> setResult(num1/num2);
                    else if (data.find('%') < data.size())
                        temporalProgrammer -> setResult(num1%num2);
                    else if (data.find('+') < data.size())
                        temporalProgrammer -> setResult(num1+num2);
                    else if (data.find('-') < data.size())
                        temporalProgrammer -> setResult(num1-num2);
                    else if (data.find('*') < data.size())
                        temporalProgrammer -> setResult(num1*num2);

                    error = false;
                }
            }while(error);
            
            do{
                cout << "Ingrese el tiempo maximo estimado del programa: ";
                cin >> num1;
                
                //el tiempo maximo estimado debe ser mayor a 0
                if(num1 > 0)
                    temporalProgrammer -> setEstimatedTime(num1);
                else
                    cout << "El tiempo maximo estimado del programa debe ser mayor a 0, intente de nuevo" << endl;
                    getchar();
            }while(num1 <= 0);

            do{
                cout << "Ingrese el ID del programa: ";
                getline(cin, data);
                for(int i(0); i<programmerVector.size(); ++i){
                    if(data == programmerVector[i]->getID()){
                        cout << "El ID ya es existente, intente de nuevo";
                        getchar();
                        error = true;
                        break;
                    }
                }
            }while(error);
            programmerVector.push_back(temporalProgrammer);
        }
    }while(option);
}

int main()
{
    vector <programmer*> programmerVector;
    int a;   
    /*
    CLEAR; //limpia la pantalla
    HIDECURSOR; //esconde el cursor
    for(int i(0); i<3; ++i) {
        GOTOXY(0,0); //modifica la posición
        SLEEP(1000); //tiempo de espera (en milisegundos)
        cout<<i<<std::endl;
    }
    SHOWCURSOR; //muestra el cursor otra vez
    cin>>a;
    */
    programmerEntry(programmerVector);
}