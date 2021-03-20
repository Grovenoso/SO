#include "batchfile.h"

void batchfile::programEntry()
{
    program *temporalProgram;
    std::vector<program *> batchVector;
    std::string data, tempData1, tempData2;
    
    bool error = true;
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
                    std::cout << std::endl << "La division entre 0 es matematicamente imposible, intente de nuevo"
                        << std::endl << "Presione enter para continuar";
                    error = true;
                    getchar();
                }

                //se realiza la operacion y se guardan los datos
                else{
                    temporalProgram->setOperation(data);

                    if (data.find('/') < data.size())
                        temporalProgram->setResult(std::to_string(num1 / num2));
                    else if (data.find('%') < data.size())
                        temporalProgram->setResult(std::to_string(num1 % num2));
                    else if (data.find('+') < data.size())
                        temporalProgram->setResult(std::to_string(num1 + num2));
                    else if (data.find('-') < data.size())
                        temporalProgram->setResult(std::to_string(num1 - num2));
                    else if (data.find('*') < data.size())
                        temporalProgram->setResult(std::to_string(num1 * num2));

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

                for (int i(0); i < batchVector.size(); i++){
                    if (data == batchVector[i]->getID()){
                        std::cout << std::endl
                                << "El ID ya es existente, intente de nuevo";
                        getchar();
                        error = true;
                        break;
                    }
                }

                if (!error){
                    temporalProgram->setID(data);
                }

            } while (error);

            //al terminar la captura de datos del programa, se añade al vector
            batchVector.push_back(temporalProgram);
            if(batchVector.size() == batchSize){
                programMatrix.push_back(batchVector);
                batchVector.clear();
            }
        }
    } while (option);
    if(batchVector.size() > 0){
        programMatrix.push_back(batchVector);
    }
}

void batchfile::programProccessing()
{
    std::vector <program*> doneAuxVector;
    int programTime, programNumber=0, inBatchProgramNumber;

    HIDECURSOR; //Hides the cursor
    for(int i(0); i<programMatrix.size(); ++i){
        
        ongoingBatch = programMatrix[i];
        inBatchProgramNumber = 0;
        
        for(int j(0); j<ongoingBatch.size(); ++j){
            CLEAR;
            programTime=0; //execution time for the current program

            //Rest of the batch in immediate queue
            GOTOXY(0,10);
            std::cout << "Lote en operacion: " << i+1;
            
            GOTOXY(0,12);
            std::cout << "Procesos pendientes del lote" << std::endl;
            for(int k(inBatchProgramNumber+1); k<ongoingBatch.size(); ++k){
                std::cout << "Nombre: " << ongoingBatch[k]->getName() << std::endl
                << "Tiempo estimado: " << ongoingBatch[k]->getEstimatedTime() << std::endl;
            }
            
            //Number of batches in queue
            std::cout << std::endl << "Lotes pendientes: " << programMatrix.size()-(i+1);

            //Batches done
            if(programNumber){
                GOTOXY(40, 0);
                std::cout << "Lotes procesados";
            }
            for(int k(0); k<doneProgramMatrix.size(); k++){
                doneAuxVector = doneProgramMatrix[k];
                
                for(int l(0); l<doneAuxVector.size(); ++l){

                    if(l%batchSize==0){
                        GOTOXY(40,(l*4)+2)
                        std::cout << "Lote # " << (l/batchSize)+1 << "  ";
                    }
                
                    GOTOXY(40,(l*4)+3)
                    std::cout << "ID: " << doneAuxVector[l]->getID();
                    GOTOXY(40,(l*4)+4)
                    std::cout << "Operacion: " << doneAuxVector[l]->getOperation();
                    GOTOXY(40, (l*4)+5)
                    std::cout << "Resultado: " << doneAuxVector[l]->getResult();
                
                    if(l%batchSize==4){
                        GOTOXY(40,((l+1)*4)+2);
                        std::cout << ".-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.";
                    }
                }
                
            }


            //Program in execution
            for(int k(ongoingBatch[j]->getEstimatedTime()); k>0; --k){
                GOTOXY(0,0);
                std::cout << "Programa en ejecución" << std::endl
                << "Nombre del Programador: " << ongoingBatch[j]->getName() << std::endl
                << "Operacion: " << ongoingBatch[j]->getOperation() << std::endl
                << "Tiempo estimado de operacion: " << ongoingBatch[j]->getEstimatedTime() << std::endl
                << "Numero de programa: " << programNumber+1 << std::endl
                << "Tiempo transcurrido: " << programTime << std::endl
                << "Tiempo restante de ejecucion: ";
                if(k<10)
                    std::cout << "0";
                std::cout << k;
                std::cout << std::endl << "Tiempo global: " << totalTime;

                SLEEP(1000); //pause (in miliseconds)
                programTime++;
                totalTime++;
            }
            programNumber++;
            inBatchProgramNumber++;
            
            doneAuxVector.push_back(ongoingBatch[j]);
            if(!doneProgramMatrix.empty())
                doneProgramMatrix.erase(doneProgramMatrix.begin()+i);
            doneProgramMatrix.push_back(doneAuxVector);
        }
        doneAuxVector.clear();
    }
    SHOWCURSOR; //shows the cursor back
}

void batchfile::createProgramEntry()
{
    //Number of programs that'll be simulated
    int programNumber;

    int number1, number2, kindOfOperation,result;

    std::string operation;
    
    //temporal program and vector for the capture
    program *temporalProgram;
    std::vector<program *> batchVector;

    //We ask the user the number of programs to be simulated
    std::cout << "Ingrese el numero de programas a procesar: ";
    std::cin >> programNumber;


    for(int i(0); i < programNumber; ++i){
        
        temporalProgram = new program();
        
        //ETA will be between 6 & 15
        temporalProgram->setEstimatedTime((rand()%9)+6);
        //ID will be the index
        temporalProgram->setID(std::to_string(i+1));

        do{
            //empties the operation string in case it resulted in a division by zero
            operation = "";
            
            //the operation will be random
            number1 = rand()%1000;
            number2 = rand()%1000;
            
            //the kind of operation can be any of the basics
            kindOfOperation = rand()%5;
            operation = std::to_string(number1);
            
            switch(kindOfOperation){
                case 0:{
                    operation += "+";
                    result = number1 + number2;
                    break;
                }
                case 1:{
                    operation += "-";
                    result = number1 - number2;
                    break;
                }
                case 2:{
                    operation += "*";
                    result = number1 * number2;
                    break;
                }
                case 3:{
                    operation += "/";
                    if(number2 != 0)
                        result = number1 / number2;
                    break;
                }
                case 4:{
                    operation += "%";
                    if (number2 != 0)
                        result = number1 % number2;
                    break;
                }
            }

            operation += std::to_string(number2);

            //set the data
            temporalProgram->setOperation(operation);
            temporalProgram->setResult(std::to_string(result));
        } while (number2 == 0 && (kindOfOperation == 3 || kindOfOperation == 4));

        batchVector.push_back(temporalProgram);
        if (batchVector.size() == batchSize){
            programMatrix.push_back(batchVector);
            batchVector.clear();
        }
    }
    
    if(batchVector.size() > 0)
        programMatrix.push_back(batchVector);
}

void batchfile::programProccessingMultiprogramation()
{
    std::vector<program *> doneAuxVector;
    program* aux;
    
    bool interruption;
    int programTime, programNumber = 0, inBatchProgramNumber;

    HIDECURSOR; //Hides the cursor
    for (int i(0); i < programMatrix.size(); ++i)
    {
        ongoingBatch = programMatrix[i];
        inBatchProgramNumber = 0;

        for (int j(0); j < ongoingBatch.size(); ++j)
        {
            CLEAR;
            programTime = ongoingBatch[j]->getTimeAlreadyDone(); //execution time for the current program

            //Rest of the batch in immediate queue
            GOTOXY(0, 0);
            std::cout << "Lote en operacion: " << i + 1;

            GOTOXY(0, 1);
            std::cout << "Procesos pendientes del lote" << std::endl;
            for (int k(inBatchProgramNumber + 1); k < ongoingBatch.size(); ++k)
            {
                std::cout << "ID: " << ongoingBatch[k]->getID() << std::endl
                          << "Tiempo estimado: " << ongoingBatch[k]->getEstimatedTime() << std::endl;
            }

            //Number of batches in queue
            std::cout << std::endl
                      << "Lotes pendientes: " << programMatrix.size() - (i + 1);

            //Batches done
            if (programNumber)
            {
                GOTOXY(80, 0);
                std::cout << "Lotes procesados";
            }
            for (int k(0); k < doneProgramMatrix.size(); k++)
            {
                doneAuxVector = doneProgramMatrix[k];

                for (int l(0); l < doneAuxVector.size(); ++l)
                {

                    if (l % batchSize == 0)
                    {
                        GOTOXY(80, (l * 4) + 2)
                        std::cout << "Lote # " << (l / batchSize) + 1 << "  ";
                    }

                    GOTOXY(80, (l * 4) + 3)
                    std::cout << "ID: " << doneAuxVector[l]->getID();
                    GOTOXY(80, (l * 4) + 4)
                    std::cout << "Operacion: " << doneAuxVector[l]->getOperation();
                    GOTOXY(80, (l * 4) + 5)
                    std::cout << "Resultado: " << doneAuxVector[l]->getResult();

                    if (l % batchSize == 4)
                    {
                        GOTOXY(80, ((l + 1) * 4) + 2);
                        std::cout << ".-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.";
                    }
                }
            }

            //Program in execution
            for (int k((ongoingBatch[j]->getEstimatedTime()-programTime)); k > 0; --k)
            {
                interruption = false;
                GOTOXY(40, 0);
                std::cout << "Programa en ejecucion";
                GOTOXY(40, 2);
                std::cout << "Operacion: " << ongoingBatch[j]->getOperation();
                GOTOXY(40, 3);
                std::cout << "Tiempo estimado de operacion: " << ongoingBatch[j]->getEstimatedTime();
                GOTOXY(40, 4);
                std::cout << "Numero de programa: " << programNumber + 1;
                GOTOXY(40, 5);
                std::cout << "Tiempo transcurrido: " << programTime;
                GOTOXY(40, 6);
                std::cout << "Tiempo restante de ejecucion: ";
                if (k < 10)
                    std::cout << "0";
                std::cout << k;
                GOTOXY(40, 7);
                std::cout << "Tiempo global: " << totalTime;

                SLEEP(1000); //pause (in miliseconds)
                programTime++;
                totalTime++;

                if(kbhit()){
                    switch(getch()){
                        case 'p':{
                            GOTOXY(0, 15);
                            std::cout << "PROGRAMA EN PAUSA, INGRESE 'C' PARA CONTINUAR";

                            while(!kbhit() && getch() != 'c'){}
                            GOTOXY(0, 15);
                            std::cout << "                                                ";
                            break;
                        }
                        
                        case 'e':{
                            k=0;
                            ongoingBatch[j]->setResult("ERROR");
                            break;
                        }

                        case 'i':{
                            k=0;
                            ongoingBatch[j]->setTimeAlreadyDone(programTime);
                            aux = ongoingBatch[j];
                            ongoingBatch.push_back(aux);
                            interruption = true;
                        }
                    }
                }

            }
            programNumber++;
            inBatchProgramNumber++;

            if(!interruption)
                doneAuxVector.push_back(ongoingBatch[j]);
            
            if (!doneProgramMatrix.empty())
                doneProgramMatrix.erase(doneProgramMatrix.begin() + i);
            doneProgramMatrix.push_back(doneAuxVector);
        }
        doneAuxVector.clear();
    }
    SHOWCURSOR; //shows the cursor back
}