#include "batchfile.h"

int main()
{
    batchfile program1;
    CLEAR;
    //program1.programEntry();
    //program1.programProccessing();
    
    program1.createProgramEntry();
    program1.programProccessingMultiprogramation();
    
    CLEAR;   
    std::cout << "HASTA LUEGO!";
    return 0;
}