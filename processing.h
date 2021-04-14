#ifndef PROCESSING_H
#define PROCESSING_H

#include "program.h"

class processing
{
    public:
        processing(){totalTime=1;}
        void programEntry();
        void createProgramEntry();

        void programProccessing();
        void programProccessingMultiprogramation();

    private:
        short totalTime, batchSize = 5;
        std::vector<std::vector<program *>> programMatrix;
        std::vector<program *> ongoingBatch;
        std::vector<std::vector<program *>> doneProgramMatrix;

};

#endif