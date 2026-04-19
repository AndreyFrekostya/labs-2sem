#include <iostream>
#pragma once
using namespace std;


class MyString {
private:
    char* data;
    int length;

public:
    MyString();
    MyString(const char* str);
    MyString(const MyString& other);
    MyString(MyString&& other);

    
    ~MyString();

    MyString& operator=(const MyString& other);
    MyString& operator=(MyString&& other);

    MyString& operator+=(const MyString& other);
    MyString& operator+=(const char * str);

    MyString operator+(const MyString& other) const;
    MyString operator+(const char * str) const;

    bool operator==(const MyString& other) const;
    bool operator==(const char * str) const;

    bool operator!=(const MyString& other) const;
    bool operator!=(const char * str) const;

    bool operator<(const MyString& other) const;
    bool operator<(const char * str) const;

    bool operator<=(const MyString& other) const;
    bool operator<=(const char * str) const;

    char& operator[](int index);                

    const char* get_full_string() const;
    char get(int i) const;
    int get_size() const;
    void set(int i, char c);
    void set_new_string(const char* str);
    void print() const;
    void read_line(istream& is = cin);
};

MyString operator+(const char * str, const MyString& other);
bool operator==(const char* str, const MyString& other);
bool operator!=(const char* str, const MyString& other);
bool operator<(const char* str, const MyString& other);
bool operator<=(const char* str, const MyString& other);

ostream& operator<<(ostream& os, const MyString& str);
istream& operator>>(istream& is, MyString& str);

MyString addTxtExtension(const MyString &path);