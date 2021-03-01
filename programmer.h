#ifndef PROGRAMMER_H
#define PROGRAMMER_H

class programmer
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