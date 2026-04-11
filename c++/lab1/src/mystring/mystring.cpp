#include "mystring.hpp"
#include <iostream>
#include <cstring>
using namespace std;

MyString::MyString() {
    data = nullptr;
    length = 0;
}

MyString::MyString(const char* str) {
    if (str) {
        length = strlen(str);
        data = new char[length + 1];
        strcpy(data, str);
    } else {
        data = nullptr;
        length = 0;
    }
}

MyString::MyString(const MyString& other) {
    data = nullptr;
    length = 0;
    *this = other;
}

MyString::~MyString() {
    cout << "Деструктор MyString" << endl;
    delete[] data;
}



MyString& MyString::operator=(const MyString& other) {
    if (this != &other) {       
        delete[] data;         
        length = other.length;
        if (other.data) {
            data = new char[length + 1];
            strcpy(data, other.data);
        } else {
            data = nullptr;
        }
    }
    return *this;
}

char MyString::get(int i) const {
    if (i >= 0 && i < length) return data[i];
    throw;
}

void MyString::set(int i, char c) {
    if(i<0 || i>=length) throw;
    
    data[i] = c;
}

int MyString::get_size() const {
    return length;
}

void MyString::set_new_string(const char* str) {
    delete[] data;

    if (str) {
        length = strlen(str);
        data = new char[length + 1];
        strcpy(data, str);
    } else {
        data = nullptr;
        length = 0;
    }
}

void MyString::print() const {
    if (data)
        cout << data << endl;
    else
        cout << "пустая строка\n";
}

void MyString::read_line() {
    delete[] data;
    data = nullptr;
    length = 0;

    int buff = 16;
    data = new char[buff];
    int index = 0;

    char c;
    while (true) {
        c = cin.get();
        if (c == '\n' || c == EOF)
            break;

        if (index >= buff - 1) {
            buff *= 2;
            char* new_data = new char[buff];
            for (int i = 0; i < index; ++i)
                new_data[i] = data[i];
            delete[] data;
            data = new_data;
        }

        data[index++] = c;
    }

    data[index] = '\0';
    length = index;
}




