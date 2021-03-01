#if _WIN64 || _WIN32
#define CLEAR system("cls")
#include <Windows.h>
#define SLEEP(x) Sleep(x);
#else
#define CLEAR system("clear");
#define SLEEP(x) std::this_thread::sleep_for(std::chrono::milliseconds(x));
#endif

#define GOTOXY(x, y) printf("%c[%d;%df", 0x1B, y, x);
#define HIDECURSOR printf("\e[?25l");
#define SHOWCURSOR printf("\e[?25h");

#include "batchfile.h"

void batchfile::programEntry(std::vector<program *> & programVector)
{
    bool error = true;
    program *temporalProgram;
    std::string data, tempData1, tempData2;
    int num1 = 0, num2 = 0, option;
    char operation;

    do{
        CLEAR;
        std::cout << "Bienvenido, si desea ingresar un nuevo programa ingrese cualquier numero"
                    <<", de lo contrario, ingrese 0: ";
        std::cin >> option;
        std::cin.ignore();

        if (option){
            temporalProgram = new program();

            std::cout << "Ingrese el nombre del programador: ";
            getline(std::cin, data);
            temporalProgram->setName(data);

            do{
                std::cout << "Ingrese la operacion que desea realizar: ";
                getline(std::cin, data);

                //separacion de la operacion a terminos numericos
                if (data.find('/') < data.size()){
                    tempData1 = data.substr(0, data.find('/'));
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

                //se lleva las strings a enteros simples para realizar la operacion
                num1 = stoi(tempData1);
                num2 = stoi(tempData2);

                //si la operacion es una division o residuo y el segundo (el divisor) es 0 se manda un error
                if (((data.find('/') < data.size()) || (data.find('%') < data.size())) && !num2){
                    std::cout << std::endl
                            << "La division entre 0 es matematicamente imposible, intente de nuevo";
                    error = true;
                    getchar();
                }

                //se realiza la operacion y se guardan los datos
                else{
                    temporalProgram->setOperation(data);

                    if (data.find('/') < data.size())
                        temporalProgram->setResult(num1 / num2);
                    else if (data.find('%') < data.size())
                        temporalProgram->setResult(num1 % num2);
                    else if (data.find('+') < data.size())
                        temporalProgram->setResult(num1 + num2);
                    else if (data.find('-') < data.size())
                        temporalProgram->setResult(num1 - num2);
                    else if (data.find('*') < data.size())
                        temporalProgram->setResult(num1 * num2);

                    error = false;
                }
            } while (error);

            do{
                std::cout << "Ingrese el tiempo maximo estimado del programa: ";
                std::cin >> num1;

                //el tiempo maximo estimado debe ser mayor a 0
                if (num1 > 0)
                    temporalProgram->setEstimatedTime(num1);
                
                else{
                    std::cout << std::endl
                        << "El tiempo maximo estimado del programa debe ser mayor a 0, intente de nuevo";
                    getchar();
                }
            } while (num1 <= 0);

            std::cin.ignore();
            do{
                error = false;
                std::cout << "Ingrese el ID del programa: ";
                getline(std::cin, data);

                for (int i(0); i < programVector.size(); i++)
                {
                    if (data == programVector[i]->getID())
                    {
                        std::cout << std::endl
                                << "El ID ya es existente, intente de nuevo";
                        getchar();
                        error = true;
                        break;
                    }
                }

                if (!error)
                {
                    temporalProgram->setID(data);
                }

            } while (error);

            //al terminar la captura de datos del programa, se añade al vector
            programVector.push_back(temporalProgram);
        }
    } while (option);
}

void batchfile::programProccessing(std::vector<program *> &programVector)
{
    HIDECURSOR; //esconde el cursor
    for (int i(0); i < programVector.size(); i++){
        std::cout << "Lote numero: " << (counter / 5) + 1 
                << " Operacion: " << counter 
                << "\t\tLotes restantes: " << (programVector.size() - counter) / 5 << std::endl;
        counter++;
        std::cout << "Nombre Programador " << programVector[i]->getName() << std::endl
                  << "ID " << programVector[i]->getID() << std::endl
                  << "Operacion " << programVector[i]->getOperation() << std::endl
                  << "Resultado " << programVector[i]->getResult() << std::endl
                  << "Tiempo estimado de operacion " << programVector[i]->getEstimatedTime() << std::endl;
        SLEEP(1000); //tiempo de espera (en milisegundos)
    }
    SHOWCURSOR; //muestra el cursor otra vez
}