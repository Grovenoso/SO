#include "processing.h"

void processing::createProgramEntry()
{
    //Number of programs that'll be simulated
    short programNumber;

    short number1, number2, kindOfOperation,result;

    std::string operation;
    
    //temporal program and vector for the capture
    program *temporalProgram;
    std::vector<program *> batchVector;

    //We ask the user the number of programs to be simulated
    std::cout << "Ingrese el numero de programas a procesar: ";
    std::cin >> programNumber;


    for(short i(0); i < programNumber; ++i){
        
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
    std::vector<program *> doneAuxVector;
    program* aux;
    
    bool shorterruption;
    short programTime, programNumber = 0, inBatchProgramNumber;

    HIDECURSOR; //Hides the cursor
    for (short i(0); i < programMatrix.size(); ++i)
    {
        ongoingBatch = programMatrix[i];
        inBatchProgramNumber = 0;

        for (short j(0); j < ongoingBatch.size(); ++j)
        {
            CLEAR;
            programTime = ongoingBatch[j]->getTimeDone(); //execution time for the current program

            GOTOXY(0, 0);
            std::cout << "Procesos listos" << std::endl;
            for (short k(inBatchProgramNumber + 1); k < ongoingBatch.size(); ++k)
            {
                std::cout << std::endl << "ID: " << ongoingBatch[k]->getID() 
                          << std::endl << "Tiempo estimado: " << ongoingBatch[k]->getETA() 
                          << std::endl << "Tiempo transcurrido: " << ongoingBatch[k]->getTimeDone() 
                          << std::endl;
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
            for (short k(0); k < doneProgramMatrix.size(); k++)
            {
                doneAuxVector = doneProgramMatrix[k];

                for (short l(0); l < doneAuxVector.size(); ++l)
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
            for (short k((ongoingBatch[j]->getETA()-programTime)); k > 0; --k)
            {
                shorterruption = false;
                GOTOXY(40, 0);
                std::cout << "Programa en ejecucion";
                GOTOXY(40, 2);
                std::cout << "Operacion: " << ongoingBatch[j]->getOperation();
                GOTOXY(40, 3);
                std::cout << "Tiempo estimado de operacion: " << ongoingBatch[j]->getETA();
                GOTOXY(40, 4);
                std::cout << "Numero de programa: " << programNumber + 1;
                GOTOXY(40, 5);
                std::cout << "Tiempo transcurrido: " << programTime;
                GOTOXY(40, 6);
                std::cout << "Tiempo restante de ejecucion: ";
                if (k < 10)
                    std::cout << "0";
                std::cout << k;
                GOTOXY(40, 8);
                std::cout << "Tiempo global: " << totalTime;

                SLEEP(600); //pause (in miliseconds)
                programTime++;
                totalTime++;

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
                            ongoingBatch[j]->setResult("ERROR");
                            break;                        

                        case 'i':
                            k=0;
                            ongoingBatch[j]->setTimeDone(programTime);
                            aux = ongoingBatch[j];
                            ongoingBatch.push_back(aux);
                            shorterruption = true;
                            break;
                    }
                }

            }
            programNumber++;
            inBatchProgramNumber++;

            if(!shorterruption)
                doneAuxVector.push_back(ongoingBatch[j]);
            
            if (!doneProgramMatrix.empty())
                doneProgramMatrix.erase(doneProgramMatrix.begin() + i);
            doneProgramMatrix.push_back(doneAuxVector);
        }
        doneAuxVector.clear();
    }
    SHOWCURSOR; //shows the cursor back
}

void processing::headTitle()
{
    /*
    procesos listos
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