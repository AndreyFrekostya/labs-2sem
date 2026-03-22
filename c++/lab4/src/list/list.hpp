#pragma once

#include "../circle/circle.hpp"
#include <cstddef>

class List {
private:
    class Node {
    public:
        Circle m_Data;
        Node* pPrev;
        Node* pNext;

        Node();                      
        Node(const Circle& c);        
    };

    Node* Head;   
    Node* Tail;   
    size_t m_size;

public:
    List();
    ~List();

    void push_front(const Circle& c);
    void push_back(const Circle& c);

    bool remove_first(const Circle& c);
    size_t remove_all(const Circle& c); 

    void clear();
    size_t get_size() const;

    void sort_by_area(); 

    void print() const;
    void print_to_file(const char* filename) const;
    void read_from_file(const char* filename);

    friend ostream& operator<<(ostream& os, const List& l);
};
