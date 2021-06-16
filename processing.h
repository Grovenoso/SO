#ifndef PROCESSING_H
#define PROCESSING_H

#include "program.h"

struct frame{
    short freeSpaces = 4;
    std::string usage = "NA";
    std::string state = "Libre";
};

class processing
{
    public:
        processing(){
            globalTime=0;
            execState = 1;
            interruption= false;
            execState = true;
            getNewProgram = false;
            suspendedBack = false;
            numberOfPrograms = 0;
            freeMemory = 168;
            frameSize = 4;

            for(int i(0); i<3; ++i){
                memory[42+i].freeSpaces = 0;
                memory[42+i].usage = "SO";
                memory[42+i].state = "Reservado";
            }

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

        //simple paging functions
        void updateMemoryState();
        void showMemory();
        void show2();

        //suspended programs
        void showSuspended();
        void writeToDisk(program* p);
        void readFromDisk();

        //function that shows all programs data and its calculated times
        void finishedProgram();
        void printData();

    private:            
        //boolean to cut the execution in case of interruption
        bool interruption;

        //number of programs that'll be created
        short numberOfPrograms;

        //value of the quantum
        short quantumValue;
        
        //times
        short globalTime;

        //free memory space
        short freeMemory;
        short frameSize;

        //execution state
        bool execState;
        bool getNewProgram;

        //program vectors
        std::vector<program *> newProgramsV;
        std::vector<program *> readyProgramsV;
        std::vector<program *> doneProgramsV;
        std::vector<program *> blockedProgramsV;
        std::vector<program *> suspendedProgramsV;

        //system memory
        frame memory[45];

        //boolean to prioritize the entrance of a suspended program than a new one
        bool suspendedBack;

        //auxiliary programs
        program *inExecutionP, *auxP;
};

#endif