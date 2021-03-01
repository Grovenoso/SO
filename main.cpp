#include "batchfile.h"

int main()
{
    vector <program*> programVector;
    batchfile program1;

    program1.programEntry(programVector);
    program1.programProccessing(programVector);
    
    /*
    int a;   
    CLEAR; //limpia la pantalla
    HIDECURSOR; //esconde el cursor
    for(int i(0); i<3; ++i) {
        GOTOXY(0,0); //modifica la posición
        SLEEP(1000); //tiempo de espera (en milisegundos)
        cout<<i<<std::endl;
    }
    SHOWCURSOR; //muestra el cursor otra vez
    cin>>a;
    */
    return 0;
}