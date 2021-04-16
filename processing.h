#ifndef PROCESSING_H
#define PROCESSING_H

#include "program.h"

class processing
{
    public:
        processing(){globalTime=0;
        actualPrograms = 0;
        execState = 1;}
        

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

        //function that shows all programs data and its calculated times
        void finishedProgram();

    private:
        //control variables
        short batchSize = 5;
        
            //number of programs that'll be created
        short numberOfPrograms;
            
            //number of programs actually created
        short actualPrograms;
            
            //indexes
        short globalProgramNumber, inBatchProgramNumber, ongoingBatchI;
        
            //times
        short globalTime;

            //execution state
        bool execState;

            //program vectors
        std::vector<std::vector<program *>> programM;
        std::vector<program *> ongoingBatchV;
        std::vector<program *> doneProgramV;
        std::vector<program *> blockedProgramsV;

            //auxiliary programs
        program *inExecutionP, *auxP;
};

#endif