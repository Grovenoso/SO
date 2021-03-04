#ifndef BATCHFILE_H
#define BATCHFILE_H

#include "program.h"

class batchfile
{
    public:
        batchfile(){totalTime=1;}
        void programEntry(std::vector<program*> &programVector);
        void programProccessing(std::vector<program *> &programVector);

    private:
        int totalTime, batchSize = 5;
};

#endif