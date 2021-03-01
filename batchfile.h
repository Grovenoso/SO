#ifndef BATCHFILE_H
#define BATCHFILE_H

#include "program.h"

class batchfile
{
    public:
        batchfile(){counter=0; totalTime=0;}
        void programEntry(std::vector<program*> &programVector);
        void programProccessing(std::vector<program *> &programVector);

    private:
        int counter, totalTime;
};

#endif