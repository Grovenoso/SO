#include "processing.h"

int main()
{
    processing program;
    CLEAR;
    
    program.createProgramEntry();
    program.displayProccessing();
    
    getch();
    CLEAR;   
    std::cout << "HASTA LUEGO!";
    return 0;
}