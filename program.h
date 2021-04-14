#ifndef PROGRAM_H
#define PROGRAM_H

#if _WIN64 || _WIN32
#define CLEAR system("cls")
#include <Windows.h>
#define SLEEP(x) Sleep(x);
#else
#define CLEAR system("clear");
#define SLEEP(x) std::this_thread::sleep_for(std::chrono::milliseconds(x));
#endif

#define GOTOXY(x, y) printf("%c[%d;%df", 0x1B, y, x);
#define HIDECURSOR printf("\e[?25l");
#define SHOWCURSOR printf("\e[?25h");

#include <iostream>
#include <cstdio>
#include <chrono>
#include <thread>
#include <string>
#include <vector>
#include <ctime>
#include <string>
#include <conio.h>

class program
{
    public:
        program() {timeDone=0;}
        
        void setName(std::string data) {name = data;};
        void setOperation(std::string data) {operation = data;};
        void setID(std::string data) {ID = data;};
        void setResult(std::string data) {result = data;};
        void setETA(short data) {ETA = data;};
        void setTimeDone(short data) {timeDone = data;};

        std::string getName() {return name;};
        std::string getOperation() {return operation;};
        std::string getID() {return ID;};
        std::string getResult() {return result;};
        short getETA() {return ETA;};
        short getTimeDone() {return timeDone;};

    private:
        std::string name, operation, ID, result;
        short num1, num2;
        
        //All times
        short ETA;
        //Calculated times
        short arrivalTime, timeDone, returnTime, responseTime, onWaitTime, onServiceTime;
};

#endif