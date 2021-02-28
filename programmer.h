#ifndef PROGRAMMER_H
#define PROGRAMMER_H

class programmer
{
    public:
        void setName(std::string data) {name = data;};
        void setOperation(std::string data) {operation = data;};
        void setEstimatedTime(std::string data) {estimatedTime = data;};
        void setID(std::string data) {ID = data;};

        std::string getName() {return name;};
        std::string getOperation() {return operation;};
        std::string getEstimatedTime() {return estimatedTime;};
        std::string getID() {return ID;};

        int doOperation();

    private:
        std::string name;
        std::string operation;
        std::string estimatedTime;
        std::string ID;

        int num1, num2;

};

#endif