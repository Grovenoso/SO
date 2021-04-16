#include "processing.h"

void processing::createProgramEntry()
{
    bool divisionByZero;
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
            //empties the operation string and resets boolean
            //in case it resulted in a division by zero
            operation = "";
            divisionByZero = false;
            
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
                    if(number2 != 0){
                        result = number1 / number2;
                        divisionByZero = true;
                    }
                    break;
                
                case 4:
                    operation += "%";
                    if (number2 != 0){
                        result = number1 % number2;
                        divisionByZero = true;
                    }
                    break;
                
            }

            operation += std::to_string(number2);

            //set the data
            temporalProgram->setOperation(operation);
            temporalProgram->setResult(std::to_string(result));
        } while (divisionByZero);

        batchVector.push_back(temporalProgram);
        actualPrograms++;
        if (batchVector.size() == batchSize){
            programM.push_back(batchVector);
            batchVector.clear();
        }
    }
    
    if(batchVector.size() > 0)
        programM.push_back(batchVector);
    CLEAR;
}

void processing::displayProccessing()
{
    HIDECURSOR; //Hides the cursor
    for(short i(0); i<programM.size(); ++i){
        ongoingBatchV = programM[i];
        for(short j(0); j<ongoingBatchV.size(); ++j){
            inBatchProgramNumber=j;
            onQueuePrograms();
            donePrograms();
            inExecutionProgram();
            CLEAR;
        }
    }
    SHOWCURSOR; //shows the cursor back
}

void processing::headTitle()
{
    //number of new programs
    GOTOXY(0,0);
    std::cout << "Procesos nuevos: " << numberOfPrograms - actualPrograms;
    
    //total number of programs
    GOTOXY(25,0);
    std::cout << "Numero total de procesos: " << actualPrograms;

    //global time count
    GOTOXY(60,0);
    std::cout << "Contador global: " << globalTime;
    
    //execution state
    GOTOXY(85, 0);
    std::cout << "Estado: " << (execState ? "en ejecucion":"pausa       ");
}

void processing::onQueuePrograms()
{
    //ready programs
    GOTOXY(0, 3);
    std::cout << "Procesos listos";

    for (short i = inBatchProgramNumber+1; i < ongoingBatchV.size(); ++i){
        std::cout << std::endl
                  << "ID: " << ongoingBatchV[i]->getID()
                  << std::endl
                  << "ETA: " << ongoingBatchV[i]->getETA()
                  << std::endl
                  << "TT: " << ongoingBatchV[i]->getTimeDone()
                  << std::endl;
    }
}

void processing::inExecutionProgram()
{   
    //boolean to cut the execution in case of interruption
    bool interruption = false;
    //program in execution
    inExecutionP = ongoingBatchV[inBatchProgramNumber];
    
    for (short i(0); i < inExecutionP->getETA(); ++i){                    
        //printing all program data
        GOTOXY(25, 3);
        std::cout << "Programa en ejecucion";
        GOTOXY(25, 4);
        std::cout << "ID: " << inExecutionP->getID();
        GOTOXY(25, 5);
        std::cout << "OP: " << inExecutionP->getOperation();
        GOTOXY(25, 6);
        std::cout << "ETA: " << inExecutionP->getETA();
        GOTOXY(25, 7);
        std::cout << "TT: " << inExecutionP->getServiceTime();
        GOTOXY(25, 8);
        std::cout << "TRE: ";
        if (inExecutionP->getETA() - i < 10)
            std::cout << "0";
        std::cout << inExecutionP->getETA() - i;

        //keyboard listening for quick actions
        if (kbhit()){
            switch (getch()){
            case 'p':
                execState = false;
                headTitle();
                while (!kbhit() && getch() != 'c'){}
                execState = true;
                headTitle();
                break;

            case 'e':
                i = inExecutionP->getETA();
                inExecutionP->setResult("ERROR");
                break;

            case 'i':
                i = inExecutionP->getETA();
                inExecutionP->setBlockedTime(5);
                blockedProgramsV.push_back(inExecutionP);
                ongoingBatchV.erase(ongoingBatchV.begin());
                interruption = true;                
                break;
            }
        }

        //parts of the screen that need to be updated every second
        headTitle();
        blockedProgramsQueue();

        //time increments
        globalTime++;
        inExecutionP->setServiceTime(inExecutionP->getServiceTime() + 1);    

        //if it's sent to blocked we pass onto the next program
        if(interruption)
            i++;

        //pause (in miliseconds)
        SLEEP(600); 
    }
    doneProgramV.push_back(inExecutionP);
}

void processing::blockedProgramsQueue()
{
    GOTOXY(25,10);
    std::cout << "Programas bloqueados";
    
    for(short i(0); i<blockedProgramsV.size(); ++i){
        GOTOXY(25,(i*3)+12);
        std::cout << "ID: " << blockedProgramsV[i]->getID();
        GOTOXY(25,(i*3)+13);
        std::cout << "TTB: " << blockedProgramsV[i]->getBlockedTime();
    }
    
    for(short i(0); i<blockedProgramsV.size(); ++i){
        if(!blockedProgramsV[i]->getBlockedTime()){
            auxP = blockedProgramsV[i];
            ongoingBatchV.push_back(auxP);
            blockedProgramsV.erase(blockedProgramsV.begin() + i);
        }
        
        blockedProgramsV[i]->setBlockedTime(blockedProgramsV[i]->getBlockedTime() - 1);
    }
}

void processing::donePrograms()
{
    GOTOXY(60, 3);
    std::cout << "Programas terminados";

    for(short i(0); i<doneProgramV.size(); ++i){
        GOTOXY(60, (i*4)+4);
        std::cout << "ID: " << doneProgramV[i]->getID();
        GOTOXY(60, (i*4)+5);
        std::cout << "OP: " << doneProgramV[i]->getOperation();
        GOTOXY(60, (i*4)+6);
        std::cout << "R: " << doneProgramV[i]->getResult();
    }
}

void processing::finishedProgram()
{
    /*
    show all shit
    */
}