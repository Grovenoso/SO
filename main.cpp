#include "processing.h"

int main()
{
    processing program;
    CLEAR;
    
    program.createProgramEntry();
    program.displayProccessing();
    /*
    program.headTitle();
    program.onQueuePrograms();
    program.inExecutionProgram();
    program.blockedProgramsQueue();
    program.donePrograms();
    */

    getch();
    CLEAR;   
    std::cout << "HASTA LUEGO!";
    return 0;
}