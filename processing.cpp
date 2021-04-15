#include "processing.h"

void processing::createProgramEntry()
{
    short number1, number2, kindOfOperation,result;

    std::string operation;
    
    //temporal program and vector for the capture
    program *temporalProgram;
    std::vector<program *> batchVector;

    //We ask the user the number of programs to be simulated
    std::cout << "Ingrese el numero de programas a procesar: ";
    std::cin >> numberOfPrograms;


    for(short i(0); i < numberOfPrograms; ++i){
        
        temporalProgram = new program();
        
        //ETA will be between 6 & 15
        temporalProgram->setETA((rand()%10)+6);
        //ID will be the index
        temporalProgram->setID(std::to_string(i+1));

        do{
            //empties the operation string in case it resulted in a division by zero
            operation = "";
            
            //the operation will be semirandom
            number1 = rand()%100;
            number2 = rand()%100;
            
            //the kind of operation can be any of the basics
            kindOfOperation = rand()%5;
            operation = std::to_string(number1);
            
            switch(kindOfOperation){
                case 0:
                    operation += "+";
                    result = number1 + number2;
                    break;
                
                case 1:
                    operation += "-";
                    result = number1 - number2;
                    break;
                
                case 2:
                    operation += "*";
                    result = number1 * number2;
                    break;
                
                case 3:
                    operation += "/";
                    if(number2 != 0)
                        result = number1 / number2;
                    break;
                
                case 4:
                    operation += "%";
                    if (number2 != 0)
                        result = number1 % number2;
                    break;
                
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

void processing::displayProccessing()
{
    program* aux;
    
    bool interruption;
    short ongoingProgramTime, programNumber = 0, inBatchProgramNumber;

    HIDECURSOR; //Hides the cursor
    for (short i(0); i < programMatrix.size(); ++i)
    {
        ongoingBatchVector = programMatrix[i];
        inBatchProgramNumber = 0;

        std::cout << "Programas nuevos: " << numberOfPrograms - programNumber + 1;

        for (short j(0); j < ongoingBatchVector.size(); ++j)
        {
            CLEAR;
            ongoingProgramTime = ongoingBatchVector[j]->getTimeDone(); //execution time for the current program

            GOTOXY(0, 0);
            std::cout << "Procesos listos" << std::endl;
            for (short k(inBatchProgramNumber + 1); k < ongoingBatchVector.size(); ++k)
            {
                std::cout << std::endl << "ID: " << ongoingBatchVector[k]->getID() 
                          << std::endl << "ETA: " << ongoingBatchVector[k]->getETA() 
                          << std::endl << "TT: " << ongoingBatchVector[k]->getTimeDone() 
                          << std::endl;
            }

            //Batches done
            if (programNumber)
            {
                GOTOXY(80, 0);
                std::cout << "Procesos terminados";
            }
            for (short k(0); k < doneProgramVector.size(); k++)
            {
                    GOTOXY(80, (k * 4) + 3)
                    std::cout << "ID: " << doneProgramVector[k]->getID();
                    GOTOXY(80, (k * 4) + 4)
                    std::cout << "OP: " << doneProgramVector[k]->getOperation();
                    GOTOXY(80, (k * 4) + 5)
                    std::cout << "R: " << doneProgramVector[k]->getResult();
            }

            //Program in execution
            for (short k((ongoingBatchVector[j]->getETA()-ongoingProgramTime)); k > 0; --k)
            {
                interruption = false;
                GOTOXY(40, 0);
                std::cout << "Programa en ejecucion";
                GOTOXY(40, 2);
                std::cout << "OP: " << ongoingBatchVector[j]->getOperation();
                GOTOXY(40, 3);
                std::cout << "ETA: " << ongoingBatchVector[j]->getETA();
                GOTOXY(40, 4);
                std::cout << "ID: " << programNumber + 1;
                GOTOXY(40, 5);
                std::cout << "TT: " << ongoingProgramTime;
                GOTOXY(40, 6);
                std::cout << "TRE: ";
                if (k < 10)
                    std::cout << "0";
                std::cout << k;
                GOTOXY(40, 8);
                std::cout << "Tiempo global: " << globalTime;

                SLEEP(600); //pause (in miliseconds)
                ongoingProgramTime++;
                globalTime++;

                if(kbhit()){
                    switch(getch()){
                        case 'p':
                            GOTOXY(40, 10);
                            std::cout << "PROGRAMA EN PAUSA, INGRESE 'C' PARA CONTINUAR";

                            while(!kbhit() && getch() != 'c'){}
                            GOTOXY(40, 10);
                            std::cout << "                                                ";
                            break;                        
                        
                        case 'e':
                            k=0;
                            ongoingBatchVector[j]->setResult("ERROR");
                            break;                        

                        case 'i':
                            k=0;
                            ongoingBatchVector[j]->setTimeDone(ongoingProgramTime);
                            aux = ongoingBatchVector[j];
                            ongoingBatchVector.push_back(aux);
                            interruption = true;
                            break;
                    }
                }

            }
            programNumber++;
            inBatchProgramNumber++;

            if(!interruption)
                doneProgramVector.push_back(ongoingBatchVector[j]);
            /*
            if (!doneProgramMatrix.empty())
                doneProgramMatrix.erase(doneProgramMatrix.begin() + i);
            doneProgramMatrix.push_back(doneAuxVector);
            */
        }
        //doneProgramVector.clear();
    }
    SHOWCURSOR; //shows the cursor back
}

void processing::headTitle()
{
    /*
    procesos nuevos
    estado de ejecucion
    contador global
    procesos nuevos (anteriormente lotes pendientes [numero de procesos, no lotes])
    */
}

void processing::onQueuePrograms()
{
    //lista de procesos listos (anteriormente lote en ejecución)
    /*
    -ID
    -ETA
    -Tiempo transcurrido
    */
}

void processing::onProcessingPrograms()
{
    /*
    same shit
    */
}

void processing::blockedProgramsQueue()
{
    /*
    -ID
    -TT
    */
}

void processing::donePrograms()
{
    /*
    -ID
    -Op
    -Resultado
    */
}

void processing::finishedProgram()
{
    /*
    show all shit
    */
}