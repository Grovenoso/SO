#ifndef PROCESSING_H
#define PROCESSING_H

#include "program.h"

class processing
{
    public:
        processing(){globalTime=0;}
        
        void createProgramEntry();

        void displayProccessing();
        void headTitle();
        void onQueuePrograms();
        void onProcessingPrograms();
        void blockedProgramsQueue();
        void donePrograms();

        void finishedProgram();

    private:
        short batchSize = 5;
        
        //control variables
        short numberOfPrograms;
            //indexes
        short ongoingProgram, programNumber, inBatchProgramNumber, ongoingProgramTime, globalTime;

            //program vectors
        std::vector<std::vector<program *>> programMatrix;
        std::vector<program *> ongoingBatchVector;
        std::vector<program *> doneProgramVector;
        std::vector<program *> blockedProgramsVector;

            //interruption (program goes to blocked)
        bool interruption;


};

#endif