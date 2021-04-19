#ifndef PROCESSING_H
#define PROCESSING_H

#include "program.h"

class processing
{
    public:
        processing(){globalTime=0;
        execState = 1;
        newProgramsBatchSize = 5;
        interruption= false;
        execState = true;
        getNewProgram = false;}

        //creates the programs
        void createProgramEntry();

        //main function that calls on the others
        void displayProccessing();
        
        //head title info 
        //(updated every second)
        void headTitle();
        
        //programs ready that are on immediate queue 
        //(updates on change of state)
        void onQueuePrograms();
        
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