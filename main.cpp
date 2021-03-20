#include "batchfile.h"

int main()
{
    while (true){
        if(kbhit()){
            if (getch() == 'g'){
                std::cout << "You pressed G" << std::endl;
            }
        }
        std::cout << "Running" << std::endl;
    }
    /*
    batchfile program1;
    program1.programEntry();
    program1.programProccessing();
    //program1.createProgramEntry();
    program1.programProccessingMultiprogramation();
    getchar();
    */
    return 0;
}