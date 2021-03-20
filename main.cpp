#include "batchfile.h"

int main()
{
    batchfile program1;
    
    /*
    program1.programEntry();
    program1.programProccessing();
    
    
    while (true){
        if(kbhit()){
            if (getch() == 'g'){
                std::cout << "You pressed G" << std::endl;
            }
        }
    }
    */
    
    program1.createProgramEntry();
    program1.programProccessingMultiprogramation();
    getchar();
    
    return 0;
}