#ifndef BATCHFILE_H
#define BATCHFILE_H

#include "program.h"

class batchfile
{
    public:
        batchfile(){totalTime=1;}
        void programEntry();
        void programProccessing();

    private:
        int totalTime, batchSize = 5;
        std::vector<std::vector<program *>> programMatrix;
        std::vector<program *> ongoingBatch;
        std::vector<std::vector<program *>> doneProgramMatrix;
};

#endif