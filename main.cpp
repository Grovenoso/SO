#include "processing.h"

int main()
{
    processing program;
    CLEAR;
    
    program.getNumberOfPrograms();
    program.displayProccessing();
    program.finishedProgram();
    getch();
    CLEAR;   
    std::cout << "HASTA LUEGO!";
    return 0;
}