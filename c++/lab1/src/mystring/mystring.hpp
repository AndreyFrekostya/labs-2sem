#pragma once

class MyString {
private:
    char* data;
    int length;

public:
    MyString();
    MyString(const char* str);
    MyString(const MyString& other);
    ~MyString();

    MyString& operator=(const MyString& other);

    char get(int i) const;
    int get_size() const;
    void set(int i, char c);
    void set_new_string(const char* str);
    void print() const;
    void read_line();
};