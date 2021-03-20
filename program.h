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
        program() {time_already_done=0;}
        
        void setName(std::string data) {name = data;};
        void setOperation(std::string data) {operation = data;};
        void setID(std::string data) {ID = data;};
        void setEstimatedTime(int data) {estimatedTime = data;};
        void setResult(std::string data) {result = data;};
        void setTimeAlreadyDone(int data) {time_already_done = data;};

        std::string getName() {return name;};
        std::string getOperation() {return operation;};
        std::string getID() {return ID;};
        int getEstimatedTime() {return estimatedTime;};
        std::string getResult() {return result;};
        int getTimeAlreadyDone() {return time_already_done;};

    private:
        std::string name, operation, ID, result;
        int num1, num2, estimatedTime, time_already_done;
};

#endif