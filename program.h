#ifndef PROGRAM_H
#define PROGRAM_H

#include <iostream>
#include <stdio.h>
#include <chrono>
#include <thread>
#include <string>
#include <vector>

using namespace std;

class program
{
    public:
        void setName(string data) {name = data;};
        void setOperation(string data) {operation = data;};
        void setID(string data) {ID = data;};
        void setEstimatedTime(int data) {estimatedTime = data;};
        void setResult(int data) {result = data;};

        string getName() {return name;};
        string getOperation() {return operation;};
        string getID() {return ID;};
        int getEstimatedTime() {return estimatedTime;};
        int getResult() {return result;};

    private:
        std::string name, operation, ID;
        int num1, num2, estimatedTime, result;
};

#endif