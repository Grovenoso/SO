#include "batchfile.h"

int main()
{
    std::vector <program*> programVector;
    batchfile program1;

    program1.programEntry(programVector);
    program1.programProccessing(programVector);
    getchar();
    return 0;
}