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
        program() {onServiceTime=0;}
        
        //setters for display data
        void setName(std::string data) {name = data;};
        void setOperation(std::string data) {operation = data;};
        void setID(std::string data) {ID = data;};
        void setResult(std::string data) {result = data;};
        void setETA(short data) {ETA = data;};
        void setDoneHour(short data) {finalizationHour = data;};

        //setters for calculated times
        void setBlockedTime(short data) {blockedTime = data;};
        void setArrivalTime(short data) {arrivalHour = data;};
        void setReturnTime(short data) {returnTime = data;};
        void setResponseTime(short data) {responseTime = data;};
        void setOnWaitTime(short data) {onHoldTime = data;};
        void setServiceTime(short data) {onServiceTime = data;};

        //getters for display data
        std::string getName() {return name;};
        std::string getOperation() {return operation;};
        std::string getID() {return ID;};
        std::string getResult() {return result;};
        short getETA() {return ETA;};

        //getters for calculated times
        short getBlockedTime() {return blockedTime;};
        short getArrivalTime() {return arrivalHour;};
        short getTimeDone() {return finalizationHour;};
        short getReturnTime() {return returnTime;};
        short getResponseTime() {return responseTime;};
        short getOnWaitTime() {return onHoldTime;};
        short getServiceTime() {return onServiceTime;};

    private:
        std::string name, operation, ID, result;
        short num1, num2;
        
        //All times
        short ETA=0, blockedTime=0;
        //Calculated times
        short arrivalHour=0, finalizationHour=0, returnTime=0, responseTime=0, onHoldTime=0, onServiceTime=0;
};

#endif