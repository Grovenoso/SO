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
#include <stdio.h>
#include <chrono>
#include <thread>
#include <string>
#include <vector>
#include <ctime>
#include <string>

class program
{
    public:
        void setName(std::string data) {name = data;};
        void setOperation(std::string data) {operation = data;};
        void setID(std::string data) {ID = data;};
        void setEstimatedTime(int data) {estimatedTime = data;};
        void setResult(int data) {result = data;};

        std::string getName() {return name;};
        std::string getOperation() {return operation;};
        std::string getID() {return ID;};
        int getEstimatedTime() {return estimatedTime;};
        int getResult() {return result;};

    private:
        std::string name, operation, ID;
        int num1, num2, estimatedTime, result;
};

#endif