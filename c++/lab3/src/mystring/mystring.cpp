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
    length = other.length;
    if (other.data) {
        data = new char[length + 1];
        strcpy(data, other.data);
    } else {
        data = nullptr;
    }
}

MyString::MyString(MyString&& other): data(other.data), length(other.length) {
    other.data=nullptr;
    other.length=0;
}

MyString::~MyString() {
    delete[] data;
}


//-------------перегрузки операторов--------------
MyString& MyString::operator=(const MyString& other) {
    cout << "Оператор = MyString" << endl;
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

MyString& MyString::operator=(MyString&& other){
    if (this == &other) return *this;

    delete[] data;

    length = other.length;
    data = other.data;
    
    other.length = 0;
    other.data = nullptr;
    
    return *this;
}

MyString& MyString::operator+=(const MyString& other) {
    if(data==nullptr && other.data==nullptr) return *this;

    char* newData = new char[length + other.length + 1];

    strcpy(newData, data);
    strcat(newData, other.data);

    delete[] data;
    data = newData;
    length += other.length;

    return *this;
}
MyString& MyString::operator+=(const char * str) {
    size_t strLen=strlen(str);

    char* newData = new char[length + strLen + 1];

    strcpy(newData, data);
    strcat(newData, str);

    delete[] data;
    data = newData;
    length += strLen;

    return *this;
}

MyString MyString::operator+(const MyString& other) const {
    MyString result(*this);
    result += other;
    return result;
}
MyString MyString::operator+(const char* str) const {
    MyString result(*this);
    result += str;
    return result;
}

bool MyString::operator==(const MyString& other) const {
    if (length != other.length) return false;
    return strcmp(data, other.data) == 0;
}
bool MyString::operator==(const char * str) const {
    return strcmp(data, str) == 0;
}

bool MyString::operator!=(const MyString& other) const {
    return !(*this == other);
}
bool MyString::operator!=(const char * str) const {
    return !(*this == str);
}

bool MyString::operator<(const MyString& other) const {
    return strcmp(data, other.data) < 0;
}
bool MyString::operator<(const char * str) const {
    return strcmp(data, str) < 0;
}

bool MyString::operator<=(const MyString& other) const {
    return strcmp(data, other.data) <= 0;
}
bool MyString::operator<=(const char * str) const {
    return strcmp(data, str) <= 0;
}

char& MyString::operator[](int index) {
    if (index < 0 || index >= length) {
        cout << "Неккоректный индекс!" << endl;
        static char out_of_bounds = '\0';
        return out_of_bounds;  
    }
    
    return data[index];
}

MyString operator+(const char * str, const MyString& other) {
    MyString result(str);    
    result += other;          
    return result;
};

bool operator==(const char* str, const MyString& other) {
    return other == str;  
}

bool operator!=(const char* str, const MyString& other) {
    return other != str;  
}

bool operator<(const char* str, const MyString& other) {
    MyString temp(str);
    return temp < other;  
}

bool operator<=(const char* str, const MyString& other) {
    MyString temp(str);
    return temp <= other;
}

ostream& operator<<(ostream& os, const MyString& str) {
    if (str.get_size() > 0) {
        os << str.get_full_string();
    } else {
        os << "";
    }
    return os;
}

istream& operator>>(istream& is, MyString& str) {
    str.read_line(is);

    return is;
}

//------------------------------------------------

const char* MyString::get_full_string() const {
    return data ? data : "";
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
        cout << "Пустая строка!\n";
}

void MyString::read_line(istream& is) {
    delete[] data;
    data = nullptr;
    length = 0;

    int buff = 16;
    data = new char[buff];
    int index = 0;

    char c;
    while (true) {
        c = is.get();
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

MyString addTxtExtension(const MyString &path) { return path + ".txt"; }


