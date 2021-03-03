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
        std::cout << "Bienvenido, si desea un nuevo ingreso ingrese cualquier numero"
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
    std::vector<program*> aux;
    int programTime;

    HIDECURSOR; //Hides the cursor
    for (int i(0); i < programVector.size(); i++){
        
        CLEAR;
        programTime = 0; //time for the program in execution
        
        //Batch in immediate queue
        GOTOXY(0,10);
        std::cout << std::endl << "Lote en operacion: " << (i/5)+1 << std::endl;
    
        GOTOXY(0,11);
        std::cout << std::endl << "Procesos pendientes del lote";
        for(int j(i+1); j%5 !=0 && j<programVector.size(); ++j){
            std::cout << std::endl << "Nombre: " << programVector.at(j)->getName() << std::endl
                << "Tiempo maximo estimado: " << programVector.at(j)->getEstimatedTime() << std::endl;
        }
        
        //Batches done
        if(i){
            GOTOXY(40,0);
            std::cout << "Lotes procesados";
        }
        for(int j(0); j<i; j++){
            //Batch done tag appears at the beggining
            if(j%5==0){
                GOTOXY(40,(j*5)+2);
                std::cout << "Lote #" << (j/5)+1;
            }
            GOTOXY(40, (j*5)+3);
            std::cout << "ID: " << programVector[j]->getID();
            GOTOXY(40, (j*5)+4);
            std::cout << "Operacion: " << programVector[j]->getOperation();
            GOTOXY(40, (j*5)+5);
            std::cout <<"Resultado: " << programVector[j]->getResult();

            //Batch done separation appears at the end of the batch
            if (j%5==4){
                GOTOXY(40, (j*5)+6);
                std::cout << ".-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.";
            }
        }

        //Program in execution
        for(int j(programVector[i]->getEstimatedTime()); j>0; --j){
            GOTOXY(0,0);
            std::cout << "Programa en ejecucion" << std::endl
                << "Nombre Programador: " << programVector[i]->getName() << std::endl
                << "Operacion: " << programVector[i]->getOperation() << std::endl
                << "Tiempo estimado de operacion: " << programVector[i]->getEstimatedTime() << std::endl
                << "Numero de programa: " << i + 1 << std::endl
                << "Tiempo transcurrido: " << programTime << std::endl
                << "Tiempo restante de ejecucion: " << j << std::endl 
                << "Tiempo global: " << totalTime;
            
            SLEEP(1000); // pause (in miliseconds)
            programTime++;
            totalTime++;
        }
    }
    
    SHOWCURSOR; //shows the cursor back
}