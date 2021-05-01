#include "processing.h"

void processing::getNumberOfPrograms()
{
    short entryNumberOfPrograms;
    //We ask the user the number of programs to be simulated
    std::cout << "Ingrese el numero de programas a procesar: ";
    std::cin >> entryNumberOfPrograms;

    entryNumberOfPrograms;
    createProgramEntry(entryNumberOfPrograms);
}

void processing::createProgramEntry(short programs)
{
    bool divisionByZero;
    short number1, number2, kindOfOperation,result;

    std::string operation;
    
    //temporal program and vector for the capture
    program *temporalProgram;

    for(short i(0); i < programs; ++i){
        
        temporalProgram = new program();
        
        //ETA will be between 6 & 15
        temporalProgram->setETA((rand()%10)+6);
        //ID will be the index
        temporalProgram->setID(std::to_string(numberOfPrograms+1));

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

        newProgramsV.push_back(temporalProgram);
        numberOfPrograms++;
    }
    CLEAR;
}

void processing::clearScreen()
{
    CLEAR;
    headTitle();
    onQueuePrograms();
    blockedProgramsQueue();
    donePrograms();
}

void processing::updateOnQueuePrograms()
{
    while ((readyProgramsV.size()+blockedProgramsV.size()+1) < 5 && !newProgramsV.empty()){
        readyProgramsV.push_back(newProgramsV[0]);
        newProgramsV.erase(newProgramsV.begin());
    }
}

void processing::displayProccessing()
{
    HIDECURSOR; //Hides the cursor
    updateOnQueuePrograms();
    //it will keep going on until the new programs queue and the ready programs are executed
    while (doneProgramV.size() != numberOfPrograms){
        //when a program enters to the memory the arrival hour has to be updated
        updateArrivalTime();
        
        if(!readyProgramsV.empty()){
            //as soon as we get the program in the front of the queue we get it off it
            inExecutionP = readyProgramsV[0];
            readyProgramsV.erase(readyProgramsV.begin());
        }

        //we restart the interruption flag
        interruption = false;

        //control variable to know if a new program can enter to the system
        getNewProgram = (readyProgramsV.size() + blockedProgramsV.size() < newProgramsBatchSize-1) && !newProgramsV.empty();

        //we evaluate if there's memory space for a new program to get in
        if (getNewProgram){
            readyProgramsV.push_back(newProgramsV[0]);
            newProgramsV.erase(newProgramsV.begin());
        }

        //we update this printings only on a change of state
        onQueuePrograms();
        donePrograms();
        inExecutionProgram();
        CLEAR;
    }
    //last program is showed on the queue
    headTitle();
    onQueuePrograms();
    donePrograms();

    //we get a pause after the program's ended
    getch();
    SHOWCURSOR; //shows the cursor back
}

void processing::headTitle()
{
    //number of new programs
    GOTOXY(0,0);
    std::cout << "Procesos nuevos: " << newProgramsV.size();
    
    //total number of programs
    GOTOXY(25,0);
    std::cout << "Numero total de procesos: " << numberOfPrograms;

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

    for (short i = 0; i < readyProgramsV.size(); ++i){
        std::cout << std::endl
                  << "ID: " << readyProgramsV[i]->getID()
                  << std::endl
                  << "TME: " << readyProgramsV[i]->getETA()
                  << std::endl
                  << "TT: " << readyProgramsV[i]->getServiceTime()
                  << std::endl;
    }
}

void processing::inExecutionProgram()
{
    if(doneProgramV.size() + blockedProgramsV.size() == numberOfPrograms){
        short timeRemaining = blockedProgramsV.front()->getBlockedTime() + 1;
        
        for (short i(0); i < timeRemaining; ++i){
            GOTOXY(25, 3);
            std::cout << "Programa en ejecucion";
            GOTOXY(25, 4);
            std::cout << "ID: --";
            GOTOXY(25, 5);
            std::cout << "OP: -----";
            GOTOXY(25, 6);
            std::cout << "TME: ---";
            GOTOXY(25, 7);
            std::cout << "TT: ---";
            GOTOXY(25, 8);
            std::cout << "TRE: ---";
            interruption = true;

            //parts of the screen that need to be updated every second
            headTitle();
            blockedProgramsQueue();

            //time increments
            globalTime++;

            //pause (in miliseconds)
            SLEEP(600);
        }
    }
    else{
        for (short i=inExecutionP->getServiceTime(); i < inExecutionP->getETA(); ++i){        

            //updating response time
            if(!inExecutionP->getServiceTime())
                updateResponseTime();

            //printing all program data
            GOTOXY(25, 3);
            std::cout << "Programa en ejecucion";
            GOTOXY(25, 4);
            std::cout << "ID: " << inExecutionP->getID();
            GOTOXY(25, 5);
            std::cout << "OP: " << inExecutionP->getOperation();
            GOTOXY(25, 6);
            std::cout << "TME: " << inExecutionP->getETA();
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
                    //if paused the execution state and its printing is updated
                    execState = false;
                    headTitle();

                    //when the execution state is continued the state
                    //and its printing are updated
                    while (!kbhit() && getch() != 'c'){}
                    execState = true;
                    headTitle();
                    break;

                case 'e':
                    //if the e key is pressed the control index 
                    //and program result are updated
                    i = inExecutionP->getETA();
                    inExecutionP->setResult("ERROR");
                    updateFinalizationHour();
                    updateOnQueuePrograms();
                    break;

                case 'i':
                    //data and program is set to the blocked vector
                    inExecutionP->setBlockedTime(5);
                    blockedProgramsV.push_back(inExecutionP);
                    updateOnQueuePrograms();

                    //interruption flag is activated
                    interruption = true;                
                    break;
                
                case 'n':
                    //create a new program
                    createProgramEntry(1);
                    updateOnQueuePrograms();
                    clearScreen();
                    break;

                case 'b':
                    bcp();
                    while (!kbhit() && getch() != 'c'){}
                    clearScreen();
                    break;
                }
            }
            if(interruption)
                return;

            //parts of the screen that need to be updated every second
            headTitle();
            blockedProgramsQueue();

            //time increments
            globalTime++;
            inExecutionP->setServiceTime(inExecutionP->getServiceTime() + 1);
            updateOnHoldTime();

            //pause (in miliseconds)
            SLEEP(600);
        }
        //if it was sent to blocked we don't add it to the done vector and
        // pass onto the next program
        inExecutionP->updateDoneState(true);
        doneProgramV.push_back(inExecutionP);
        updateFinalizationHour();
    }
}

void processing::blockedProgramsQueue()
{
    GOTOXY(25,10);
    std::cout << "Programas bloqueados";
    
    for(short i(0); i<blockedProgramsV.size(); ++i){
        GOTOXY(25,(i*3)+12);
        std::cout << "ID: " << blockedProgramsV[i]->getID();
        GOTOXY(25,(i*3)+13);
        std::cout << "TRB: " << blockedProgramsV[i]->getBlockedTime();

        if (blockedProgramsV[i]->getBlockedTime()==0){
            auxP = blockedProgramsV[i];
            readyProgramsV.push_back(auxP);
            blockedProgramsV.erase(blockedProgramsV.begin()+i);
            
            onQueuePrograms();
            //when a program stops beign blocked
            //the blocked programs queue the head title
            //the ready programs queue and potentially the programs that are done
            //should be updated
            for(short j(0); j<blockedProgramsV.size()+1; ++j){
                GOTOXY(25, (j * 3) + 12);
                std::cout << "      ";
                GOTOXY(25, (j * 3) + 13);
                std::cout << "      ";
            }
        }
        
        else
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

void processing::updateArrivalTime()
{
    for(short i(0); i<readyProgramsV.size(); ++i){
        auxP = readyProgramsV[i];
        if(auxP->getArrivalTime() == -1)
            auxP->setArrivalTime(globalTime);
    }
}

void processing::updateFinalizationHour()
{
    inExecutionP->setFinalizationHour(globalTime);
    updateReturnTime();
}

void processing::updateReturnTime()
{
    inExecutionP->setReturnTime(inExecutionP->getFinalizationHour() - inExecutionP->getArrivalTime());
}

void processing::updateResponseTime()
{
    inExecutionP->setResponseTime(globalTime - inExecutionP->getArrivalTime());
}

void processing::updateOnHoldTime()
{
    for (short i = 0; i<readyProgramsV.size(); ++i){
        readyProgramsV[i]->setOnHoldTime(auxP->getOnHoldTime() + 1);
    }
}

void processing::bcp()
{
    CLEAR;

    //done programs
    for (short i(0); i < doneProgramV.size(); ++i){
        auxP = doneProgramV[i];
        printData();
    }
    
    //in execution program
    auxP = inExecutionP;
    printData();
    
    //ready programs
    for(short i(0); i < readyProgramsV.size(); ++i){
        auxP = readyProgramsV[i];
        printData();
    }
    
    //blocked programs
    for(short i(0); i < blockedProgramsV.size(); ++i){
        auxP = blockedProgramsV[i];
        printData();
    }
    
    //new programs
    for(short i(0); i < newProgramsV.size(); ++i){
        auxP = newProgramsV[i];
        printData();
    }

}

void processing::printData()
{
    std::cout << "ID: " << auxP->getID() << std::endl
              << "OP: " << auxP->getOperation() << std:: endl
              << "R: " << (auxP->getDoneState() ? auxP->getResult() : "-1") << std::endl
              << "TME: " << auxP->getETA() << std::endl
              << "T Llegada: " << auxP->getArrivalTime() << std::endl
              << "T Finalizacion: " << auxP->getFinalizationHour() << std::endl
              << "T Retorno: " << auxP->getReturnTime() << std::endl
              << "T Respuesta: " << auxP->getResponseTime() << std::endl
              << "T Espera: " << auxP->getOnHoldTime() << std::endl
              << "T Servicio: " << auxP->getServiceTime() << std::endl << std::endl;
}

void processing::finishedProgram()
{
    CLEAR;
    for(short i(0); i<doneProgramV.size(); ++i){
        auxP = doneProgramV[i];
        printData();
    }
}
