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
        program() {
            ETA=-1; 
            finalizationHour=-1;
            blockedTime=-1;
            arrivalHour=-1; 
            returnTime=-1; 
            responseTime=-1;
            onHoldTime=-1; 
            onServiceTime=0;
        }
        
        //setters for display data
        void setOperation(std::string data) {operation = data;};
        void setID(std::string data) {ID = data;};
        void setResult(std::string data) {result = data;};

        //setters for all times
        void setETA(short data) {ETA = data;};
        void setFinalizationHour(short data) {finalizationHour = data;};
        void setBlockedTime(short data) {blockedTime = data;};
        void setArrivalTime(short data) {arrivalHour = data;};
        void setReturnTime(short data) {returnTime = data;};
        void setResponseTime(short data) {responseTime = data;};
        void setOnHoldTime(short data) {onHoldTime = data;};
        void setServiceTime(short data) {onServiceTime = data;};

        //getters for display data
        std::string getOperation() {return operation;};
        std::string getID() {return ID;};
        std::string getResult() {return result;};

        //getters for all times
        short getETA() {return ETA;};
        short getFinalizationHour() {return finalizationHour;};
        short getBlockedTime() {return blockedTime;};
        short getArrivalTime() {return arrivalHour;};
        short getReturnTime() {return returnTime;};
        short getResponseTime() {return responseTime;};
        short getOnHoldTime() {return onHoldTime;};
        short getServiceTime() {return onServiceTime;};

    private:
        std::string name, operation, ID, result;
        short num1, num2;
        
        //All times
        short ETA, blockedTime, arrivalHour, finalizationHour, returnTime, responseTime, onHoldTime, onServiceTime;
};

#endif