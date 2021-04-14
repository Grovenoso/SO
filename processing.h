#ifndef PROCESSING_H
#define PROCESSING_H

#include "program.h"

class processing
{
    public:
        processing(){totalTime=1;}
        
        void createProgramEntry();

        void displayProccessing();
        void headTitle();
        void onQueuePrograms();
        void onProcessingPrograms();
        void blockedProgramsQueue();
        void donePrograms();

        void finishedProgram();

    private:
        short totalTime, batchSize = 5;
        std::vector<std::vector<program *>> programMatrix;
        std::vector<program *> ongoingBatch;
        std::vector<std::vector<program *>> doneProgramMatrix;

};

#endif