#ifndef BATCHFILE_H
#define BATCHFILE_H

#include "program.h"

class batchfile
{
    public:
        void programEntry(vector<program*> &programVector);
        void programProccessing(vector<program *> &programVector);

    private:
        int counter, totalTime;
};

#endif