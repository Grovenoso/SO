#include "processing.h"

void processing::getNumberOfPrograms()
{
    short entryNumberOfPrograms;
    
    //We ask the user the number of programs to be simulated and the quantum
    do{
        std::cout << "Ingrese el numero de programas a procesar: ";
        std::cin >> entryNumberOfPrograms;
    }while(entryNumberOfPrograms < 1);
    
    do{        
        std:: cout << "Ingrese el valor del Quantum (mayor a 0 pero no mayor a 14): ";
        std::cin >> quantumValue;
    }while(quantumValue > 14 || quantumValue < 1);

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
        //we set the quantum
        temporalProgram->setQuantum(quantumValue);
        //weight will be between 5 & 25
        temporalProgram->setWeight((rand()%21)+5);

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

        temporalProgram->setState("nuevo");
        newProgramsV.push_back(temporalProgram);
        numberOfPrograms++;
    }
    CLEAR;
    updateOnQueuePrograms();
}

void processing::clearScreen()
{
    CLEAR;
    headTitle();
    onQueuePrograms();
    blockedProgramsQueue();
    donePrograms();
    showSuspended();
}

void processing::updateOnQueuePrograms()
{
    int programWeight;
    
    while(freeMemory > 0 && suspendedBack){
        if(freeMemory >= suspendedProgramsV[0]->getWeight()){
            programWeight = suspendedProgramsV[0]->getWeight();
            
            for(int i(0); i<43 && programWeight; ++i){
                if(memory[i].freeSpaces == frameSize){
                    if(programWeight >= frameSize){
                        memory[i].freeSpaces = 0;
                        programWeight -= frameSize;
                    }
                    else{
                        memory[i].freeSpaces = frameSize - programWeight;                    
                        programWeight = 0;
                    }
                    
                    memory[i].state = "Bloqueado";
                    memory[i].usage = suspendedProgramsV[0]->getID();
                    freeMemory -= 4;
                }
            }
            suspendedProgramsV[0]->setState("bloqueado");
            blockedProgramsV.push_back(suspendedProgramsV[0]);
            suspendedProgramsV.erase(suspendedProgramsV.begin()+0);
            suspendedBack = false;
        }
        else
            break;
    }

    while(freeMemory > 0 && !newProgramsV.empty() && !suspendedBack){
        
        if(freeMemory >= newProgramsV[0]->getWeight()){
            programWeight = newProgramsV[0]->getWeight();
            
            for(int i(0); i<43 && programWeight; ++i){
                if(memory[i].freeSpaces == frameSize){
                    if(programWeight >= frameSize){
                        memory[i].freeSpaces = 0;
                        programWeight -= frameSize;
                    }
                    else{
                        memory[i].freeSpaces = frameSize - programWeight;                    
                        programWeight = 0;
                    }
                    
                    memory[i].state = "Listo";
                    memory[i].usage = newProgramsV[0]->getID();
                    freeMemory -= 4;
                }
            }
            newProgramsV[0]->setState("listo");
            readyProgramsV.push_back(newProgramsV[0]);
            newProgramsV.erase(newProgramsV.begin()+0);
        }

        else
            return;
    }
}

void processing::updateMemoryState()
{
    for(int i(0); i<43; ++i){
        if(!doneProgramsV.empty())
            if(memory[i].usage == doneProgramsV.back()->getID()){
                memory[i].freeSpaces = frameSize;
                memory[i].usage = "NA";
                memory[i].state = "Libre";
                freeMemory += frameSize;
            }
        if(!suspendedProgramsV.empty())
            if(memory[i].usage == suspendedProgramsV.back()->getID()){
                memory[i].freeSpaces = frameSize;
                memory[i].usage = "NA";
                memory[i].state = "Libre";
                freeMemory += frameSize;
            }

        if (!blockedProgramsV.empty())
            if (memory[i].usage == blockedProgramsV.back()->getID())
                memory[i].state = "Bloqueado";

        if(inExecutionP != NULL)
            if (memory[i].usage == inExecutionP->getID())
                memory[i].state = "En ejecucion";
        
        for(int j(0); j<readyProgramsV.size(); ++j){
            if (memory[i].usage == readyProgramsV[j]->getID() && memory[i].state != "Listo")
                memory[i].state = "Listo";
        }
    }
}

void processing::showMemory()
{
    CLEAR;
    GOTOXY(30,0);
    std::cout << YELLOW << " -- Tabla de paginas -- " << RESET;
    GOTOXY(25, 2);
    std::cout << " # " << " Espacio " << " Proceso " << " Estado ";
    for(int i(0); i<45; ++i){
        // #
        GOTOXY(25, i+3);
        std::cout << " " << i;
        
        // Espacio
        for(int j(0); j < frameSize - memory[i].freeSpaces; ++j){
            GOTOXY(30+j, i+3);
            std::cout << CYAN << "O" << RESET;
        }
        for (int j(0); j < memory[i].freeSpaces; ++j){
            GOTOXY(30 + j + (frameSize - memory[i].freeSpaces), i + 3);
            std::cout << YELLOW << "-" << RESET;
        }
        
        //Proceso
        GOTOXY(41, i + 3);
        std::cout << memory[i].usage;

        //Estado
        GOTOXY(47, i + 3);
        if (memory[i].state == "Bloqueado")
            std::cout << RED << memory[i].state << RESET;
        else if(memory[i].state == "En ejecucion")
            std::cout << GREEN << memory[i].state << RESET;
        else if(memory[i].state == "Listo")
            std::cout << MAGENTA << memory[i].state << RESET;
        else
            std::cout << YELLOW << memory[i].state << RESET;
    }
}

void processing::displayProccessing()
{
    HIDECURSOR; //Hides the cursor
    updateOnQueuePrograms();
    
    //it will keep going on until the new programs queue and the ready programs are executed
    while (doneProgramsV.size() != numberOfPrograms){
        
        //when a program enters to the memory the arrival hour has to be updated
        updateArrivalTime();
        
        if(!readyProgramsV.empty()){
            //as soon as we get the program in the front of the queue we get it off it
            inExecutionP = readyProgramsV[0];
            readyProgramsV.erase(readyProgramsV.begin());
            updateMemoryState();
        }
        else{
            inExecutionP = NULL;
        }

        //we restart the interruption flag
        interruption = false;

        //we evaluate if there's memory space for a new program to get in
        if (freeMemory > 0){
            updateOnQueuePrograms();
        }

        //we update this printings only on a change of state
        onQueuePrograms();
        donePrograms();
        showSuspended();
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
    std::cout << "Procesos nuevos: " << YELLOW << newProgramsV.size() << RESET;

    //next program on queue
    GOTOXY(0,3);
    std::cout << MAGENTA << "Siguiente por entrar" << RESET << std::endl;
    std::cout << "ID: " << (newProgramsV.empty() ? "--" : newProgramsV[0]->getID()) << std::endl
              << "Peso: " << (newProgramsV.empty() ? "--" : std::to_string(newProgramsV[0]->getWeight()));

    //total number of programs
    GOTOXY(25, 0);
    std::cout << "Numero total de procesos: " << YELLOW << numberOfPrograms << RESET;

    //quantum value
    GOTOXY(60, 0);
    std::cout << "Quantum: " << YELLOW << quantumValue << RESET;

    //global time count
    GOTOXY(75,0);
    std::cout << "Contador global: " << YELLOW << globalTime << RESET;
    
    //execution state
    GOTOXY(100, 0);
    std::cout << "Estado: ";
    
    if(execState)
    std::cout << YELLOW << "en ejecucion";
    else
        std::cout << RED << "pausa       "; 
    
    std::cout << RESET;
}

void processing::onQueuePrograms()
{
    //ready programs
    GOTOXY(0, 7);
    std::cout << GREEN << "Procesos listos" << RESET;

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
    while(inExecutionP == NULL){
        GOTOXY(25, 3);
        std::cout << YELLOW << "Programa en ejecucion" << RESET;
        GOTOXY(25, 4);
        std::cout << "ID:" << YELLOW << " --" << RESET;
        GOTOXY(25, 5);
        std::cout << "OP:" << YELLOW << " -----" << RESET;
        GOTOXY(25, 6);
        std::cout << "TME:" << YELLOW << " ---" << RESET;
        GOTOXY(25, 7);
        std::cout << "TT:" << YELLOW << " ---" << RESET;
        GOTOXY(25, 8);
        std::cout << "TRE:" << YELLOW << " ---" << RESET;
        interruption = true;

        //keyboard listening for quick actions
        if (kbhit()){
            switch (getch()){
            case 'p': case 'P':
                //if paused the execution state and its printing is updated
                execState = false;
                headTitle();

                //when the execution state is continued the state
                //and its printing are updated
                while (!kbhit() && getch() != 'c'){}
                execState = true;
                headTitle();
                break;
            
            case 'n': case 'N':
                //create a new program
                createProgramEntry(1);
                updateOnQueuePrograms();
                clearScreen();
                break;

            case 'b': case 'B':
                bcp();
                while (!kbhit() && getch() != 'c'){}
                clearScreen();
                break;

            case 'a': case 'A':
                updateMemoryState();
                showMemory(); 
                while (!kbhit() && getch() != 'c'){}
                clearScreen();
                break;
            
            case 's': case 'S':
                if(!blockedProgramsV.empty()){
                    //change its state, sent to suspended, written to disk
                    blockedProgramsV[0]->setState("suspendido");
                    suspendedProgramsV.push_back(blockedProgramsV[0]);
                    writeToDisk(blockedProgramsV[0]);
                    
                    //erase it from blocked and update the queues
                    blockedProgramsV.erase(blockedProgramsV.begin());
                    clearScreen();
                }
                break;

            case 'r': case 'R':
                //we take back the program from the disk
                if(!suspendedProgramsV.empty()){
                    readFromDisk();
                    auxP = suspendedProgramsV[0];
                    auxP->setBlockedTime(5);
                    suspendedBack = true;
                    updateOnQueuePrograms();

                    //update queue's printing
                    showSuspended();
                    blockedProgramsQueue();
                }
                break;

            default:
                break;
            }
        }

        //parts of the screen that need to be updated every second
        headTitle();
        blockedProgramsQueue();

        //pause (in miliseconds)
        SLEEP(700);
        //time increments
        globalTime++;
        
        //each second we check if there's a new program to execute
        if(!readyProgramsV.empty() || !newProgramsV.empty())
            return;
    }

    for (short i=inExecutionP->getServiceTime(); i < inExecutionP->getETA(); ++i){        

        //updating response time
        if(!inExecutionP->getServiceTime())
            updateResponseTime();
        
        inExecutionP->setState("en ejecucion");
        //printing all program data
        GOTOXY(25, 3);
        std::cout << YELLOW << "Programa en ejecucion" << RESET;
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

        GOTOXY(25, 9);
        std::cout << "Q: "; 
        if (inExecutionP->getQuantum() < 10)
            std::cout << "0";
        std::cout << inExecutionP->getQuantum();

        //keyboard listening for quick actions
        if (kbhit()){
            switch (getch()){
            case 'p': case 'P':
                //if paused the execution state and its printing is updated
                execState = false;
                headTitle();

                //when the execution state is continued the state
                //and its printing are updated
                while (!kbhit() && getch() != 'c'){}
                execState = true;
                headTitle();
                break;

            case 'e': case 'E':
                //if the e key is pressed the control index
                //and program result are updated
                i = inExecutionP->getETA() + 1;
                inExecutionP->setResult("ERROR");
                updateFinalizationHour();
                updateOnQueuePrograms();
                break;

            case 'i': case 'I':
                //data and program is set to the blocked vector
                inExecutionP->setBlockedTime(5);
                inExecutionP->setState("bloqueado");
                inExecutionP->setQuantum(quantumValue);
                blockedProgramsV.push_back(inExecutionP);
                updateMemoryState();

                //interruption flag is activated
                interruption = true;                
                break;
            
            case 'n': case 'N':
                //create a new program
                createProgramEntry(1);
                updateOnQueuePrograms();
                clearScreen();
                break;

            case 'b': case 'B':
                bcp();
                while (!kbhit() && getch() != 'c'){}
                clearScreen();
                break;

            case 'a': case 'A':
                updateMemoryState();
                showMemory(); 
                while (!kbhit() && getch() != 'c'){}
                clearScreen();
                break;
            
            case 's': case 'S':
                if(!blockedProgramsV.empty()){
                    //change its state, sent to suspended, written to disk
                    blockedProgramsV[0]->setState("suspendido");
                    suspendedProgramsV.push_back(blockedProgramsV[0]);
                    writeToDisk(blockedProgramsV[0]);
                    
                    //erase it from blocked and update the queues
                    blockedProgramsV.erase(blockedProgramsV.begin()+0);
                    updateMemoryState();

                    //we check if there's the space for a new one
                    updateOnQueuePrograms();
                    updateMemoryState();
                    clearScreen();
                }
                break;

            case 'r': case 'R':
                if(!suspendedProgramsV.empty()){
                    //we take back the program from the disk
                    readFromDisk();
                    auxP = suspendedProgramsV[0];
                    auxP->setBlockedTime(5);
                    suspendedBack = true;
                    updateOnQueuePrograms();

                    //update queue's printing
                    showSuspended();
                    blockedProgramsQueue();
                }
                break;
            
            default:
                break;
            }
        }
        if(interruption)
            return;

        //parts of the screen that need to be updated every second
        headTitle();
        blockedProgramsQueue();

        //pause (in miliseconds)
        SLEEP(700);
        
        //time increments
        globalTime++;
        inExecutionP->setServiceTime(inExecutionP->getServiceTime() + 1);
        updateOnHoldTime();
        
        //quantum decreases
        inExecutionP->setQuantum(inExecutionP->getQuantum()-1);

        if(inExecutionP->getQuantum() < 1){
            inExecutionP->setQuantum(quantumValue);
            break;
        }
    }

    if(inExecutionP->getServiceTime() == inExecutionP->getETA() || inExecutionP->getResult() == "ERROR"){
        //if it was sent to blocked we don't add it to the done vector and
        // pass onto the next program
        inExecutionP->updateDoneState(true);
        inExecutionP->setState("terminado");
        doneProgramsV.push_back(inExecutionP);
        updateFinalizationHour();
    }
    else{
        inExecutionP->updateDoneState(false);
        inExecutionP->setState("listo");
        readyProgramsV.push_back(inExecutionP);
    }
}


void processing::blockedProgramsQueue()
{
    GOTOXY(25,11);
    std::cout << RED << "Programas bloqueados" << RESET;
    
    for(short i(0); i<blockedProgramsV.size(); ++i){
        GOTOXY(25,(i*3)+13);
        std::cout << "ID: " << blockedProgramsV[i]->getID();
        GOTOXY(25,(i*3)+14);
        std::cout << "TRB: " << blockedProgramsV[i]->getBlockedTime();

        if (blockedProgramsV[i]->getBlockedTime()==0){
            auxP = blockedProgramsV[i];
            auxP->setState("listo");
            readyProgramsV.push_back(auxP);
            blockedProgramsV.erase(blockedProgramsV.begin()+i);
            
            onQueuePrograms();
            clearScreen();
        }
        
        else
            blockedProgramsV[i]->setBlockedTime(blockedProgramsV[i]->getBlockedTime() - 1);
    }
}

void processing::donePrograms()
{
    GOTOXY(60, 3);
    std::cout << CYAN << "Programas terminados" << RESET;

    for(short i(0); i<doneProgramsV.size(); ++i){
        GOTOXY(60, (i*4)+4);
        std::cout << "ID: " << doneProgramsV[i]->getID();
        GOTOXY(60, (i*4)+5);
        std::cout << "OP: " << doneProgramsV[i]->getOperation();
        GOTOXY(60, (i*4)+6);
        std::cout << "R: " << doneProgramsV[i]->getResult();
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
{inExecutionP->setReturnTime(inExecutionP->getFinalizationHour() - inExecutionP->getArrivalTime());}

void processing::updateResponseTime()
{inExecutionP->setResponseTime(globalTime - inExecutionP->getArrivalTime());}

void processing::updateOnHoldTime()
{
    for (short i = 0; i<readyProgramsV.size(); ++i)
        readyProgramsV[i]->setOnHoldTime(auxP->getOnHoldTime() + 1);    
}

void processing::bcp()
{
    CLEAR;

    //done programs
    for (short i(0); i < doneProgramsV.size(); ++i){
        auxP = doneProgramsV[i];
        printData();
    }
    
    //in execution program
    if(inExecutionP != NULL){
        auxP = inExecutionP;
        printData();
    }
    
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
    
    //suspended programs
    for (short i(0); i < suspendedProgramsV.size(); ++i){
        auxP = suspendedProgramsV[i];
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
              << "Estado: "; 
            
    if (auxP->getState() == "nuevo")
        std::cout << MAGENTA;
    else if (auxP->getState() == "listo")
        std::cout << GREEN;
    else if (auxP->getState() == "en ejecucion")
        std::cout << YELLOW;
    else if (auxP->getState() == "bloqueado" || auxP->getState() == "suspendido")
        std::cout << RED;
    else
        std::cout << CYAN;
        
    std::cout << auxP->getState() <<  RESET << std::endl
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
    for(short i(0); i<doneProgramsV.size(); ++i){
        auxP = doneProgramsV[i];
        printData();
    }
}

void processing::writeToDisk(program* p)
{
    std::fstream sFile("suspended.txt", std::ios::out | std::ios::app);
    if(sFile.is_open()){
        sFile << "ID:"<< p->getID() << '~';
        sFile << "Peso:" << p->getWeight() << '~';
        sFile << "OP:" << p->getOperation() << '\n';
        sFile.close();
    }
}

void processing::readFromDisk()
{
    std::fstream sFile("suspended.txt", std::ios::in);
    std::fstream sFileAux("auxiliary.txt", std::ios::out | std::ios::app);
    std::string line;
    int weight;

    std::vector<program> pArray;
    program pAuxArray;

    if(sFile.is_open() && sFileAux.is_open()){
        getline(sFile, line, '~');
        getline(sFile, line, '~');
        getline(sFile, line, '\n');
        
        pArray.clear();
        
        while(!sFile.eof()){
            //ID
            getline(sFile, line, ':');
            getline(sFile, line, '~');
            pAuxArray.setID(line);

            if(sFile.eof())
                break;

            //Weight
            getline(sFile, line, ':');
            getline(sFile, line, '~');
            weight = stoi(line);
            pAuxArray.setWeight(weight);

            //Op
            getline(sFile, line, ':');
            getline(sFile, line, '\n');
            pAuxArray.setOperation(line);
            
            
            pArray.push_back(pAuxArray);
        }
        for(short i(0); i<pArray.size(); ++i){
            pAuxArray = pArray[i];
            sFileAux << "ID:" << pAuxArray.getID() << '~';
            sFileAux << "Peso:" << pAuxArray.getWeight() << '~';
            sFileAux << "OP:" << pAuxArray.getOperation() << '\n';
        }

        sFile.close();
        sFileAux.close();
        remove("suspended.txt");
        rename("auxiliary.txt", "suspended.txt");
    }
}

void processing::showSuspended()
{
    GOTOXY(90, 3);
    std::cout << RED << "Suspendidos: " << YELLOW << suspendedProgramsV.size() << RESET;

    GOTOXY(90,4);
    std::cout << "ID: ";
    if (suspendedProgramsV.empty())
        std::cout << "--";
    else{
        if (stoi(suspendedProgramsV[0]->getID()) < 10)
            std::cout << "0";
        std::cout << suspendedProgramsV[0]->getID();
    } 

    GOTOXY(90, 5);
    std::cout << "Peso: ";
    if (suspendedProgramsV.empty())
        std::cout << "--";
    else{
        if (suspendedProgramsV[0]->getWeight() < 10)
            std::cout << "0";
        std::cout << suspendedProgramsV[0]->getWeight();
    }
}