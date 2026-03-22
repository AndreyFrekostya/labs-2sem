#include "worker_data.hpp"
#include "../mystring/mystring.hpp"

WorkerData::WorkerData():name(MyString()), age(0), salary(0) {}

WorkerData::WorkerData(char* _name, unsigned char _age, double _salary):
    name(MyString(_name)), age(_age), salary(_salary) {}

WorkerData::WorkerData(const WorkerData& other):
    name(MyString(other.name)), age(other.age), salary(other.salary) {}

WorkerData::~WorkerData() {}

WorkerData& WorkerData::operator=(const WorkerData& other){
    if (this != &other) {       
        name=MyString(other.name);
        age=other.age;
        salary=other.salary;
    }
    return *this;
}   

MyString WorkerData::get_name() const { return name; }
unsigned char WorkerData::get_age() const { return age; }
double WorkerData::get_salary() const { return salary; }

