#ifndef PROCESSING_H
#define PROCESSING_H

#include "program.h"

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define RESET "\x1b[0m"

/*
Processes states
NUEVO
LISTO
EN EJECUCIÓN
BLOQUEADO
TERMINADO
*/

class processing
{
    public:
        processing(){
            globalTime=0;
            execState = 1;
            newProgramsBatchSize = 5;
            interruption= false;
            execState = true;
            getNewProgram = false;
            numberOfPrograms = 0;

            srand(time(NULL));
        }

        //creates the programs
        void createProgramEntry(short programs);
        void getNumberOfPrograms();

        //main function that calls on the others
        void displayProccessing();
        
        //function that clears the screen and calls 
        //out the others functions to show data
        void clearScreen();

        //head title info 
        //(updated every second)
        void headTitle();
        
        //programs ready that are on immediate queue 
        //(updates on change of state)
        void onQueuePrograms();
        void updateOnQueuePrograms();
        
        //program that's actually in exection
        //(updates on change of state)
        void inExecutionProgram();
        
        //shows the queue of the programs that are blockes
        //(updates every second)
        void blockedProgramsQueue();
        
        //queue that shows all programs that already done
        //(updates on change of state)
        void donePrograms();

        //calculated times functions
        void updateArrivalTime();
        void updateFinalizationHour();
        void updateReturnTime();
        void updateResponseTime();
        void updateOnHoldTime();

        //BCP function that shows all program data in the middle of execution
        void bcp();

        //function that shows all programs data and its calculated times
        void finishedProgram();
        void printData();

    private:
        //control variables
        short newProgramsBatchSize;
            
            //boolean to cut the execution in case of interruption
        bool interruption;

        //number of programs that'll be created
        short numberOfPrograms;

        //value of the quantum
        short quantumValue;
            
            //indexes
        short inBatchProgramNumber;
        
            //times
        short globalTime;

            //execution state
        bool execState;
        bool getNewProgram;

            //program vectors
        std::vector<program *> newProgramsV;
        std::vector<program *> readyProgramsV;
        std::vector<program *> doneProgramV;
        std::vector<program *> blockedProgramsV;

            //auxiliary programs
        program *inExecutionP, *auxP;
};

#endif