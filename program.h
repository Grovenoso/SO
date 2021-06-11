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

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define RESET "\x1b[0m"

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
            onHoldTime=0; 
            onServiceTime=0;
            done=false;
        }
        
        //setters for display data
        void setOperation(std::string data) {operation = data;};
        void setID(std::string data) {ID = data;};
        void setResult(std::string data) {result = data;};
        void setState(std::string data) {state = data;};
        void setWeight(short data) {weight = data;};

        //setters for all times
        void setQuantum(short data) {quantum = data;};
        void setETA(short data) {ETA = data;};
        void setFinalizationHour(short data) {finalizationHour = data;};
        void setBlockedTime(short data) {blockedTime = data;};
        void setArrivalTime(short data) {arrivalHour = data;};
        void setReturnTime(short data) {returnTime = data;};
        void setResponseTime(short data) {responseTime = data;};
        void setOnHoldTime(short data) {onHoldTime = data;};
        void setServiceTime(short data) {onServiceTime = data;};

        void updateDoneState(bool data){done = data;};
        
        //getters for display data
        std::string getOperation() {return operation;};
        std::string getID() {return ID;};
        std::string getResult() {return result;};
        std::string getState() {return state;};
        short getWeight() {return weight;};

        //getters for all times
        short getQuantum() {return quantum;};
        short getETA() {return ETA;};
        short getFinalizationHour() {return finalizationHour;};
        short getBlockedTime() {return blockedTime;};
        short getArrivalTime() {return arrivalHour;};
        short getReturnTime() {return returnTime;};
        short getResponseTime() {return responseTime;};
        short getOnHoldTime() {return onHoldTime;};
        short getServiceTime() {return onServiceTime;};

        bool getDoneState(){return done;};

    private:
        std::string name, operation, ID, result, state;
        short num1, num2, quantum, weight;
        bool done;
        
        //All times
        short ETA, blockedTime, arrivalHour, finalizationHour, returnTime, responseTime, onHoldTime, onServiceTime;
};

#endif