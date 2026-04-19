#pragma once
#include "../mystring/mystring.hpp"

class WorkerData{
private:
    MyString name;
    unsigned char age;
    double salary;

public:
    WorkerData();
    WorkerData(char* name, unsigned char age, double salary);
    WorkerData(const WorkerData& other);
    ~WorkerData();

    WorkerData& operator=(const WorkerData& other);

    MyString get_name() const;
    unsigned char get_age() const;
    double get_salary() const;
};