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

    Node* split(Node* head);
    Node* merge_sorted(Node* left, Node* right);
    Node* merge_sort(Node* head);

    void init_empty();
    void copy_from(const List& other);

public:
    class Iterator {
    private:
        Node* current;

    public:
        Iterator(Node* node);

        const Circle& operator*() const;
        Iterator& operator++();

        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;
    };

    Iterator begin() const;
    Iterator end() const;


    List();
    ~List();

    List(const List& other);
    List& operator=(const List&other);

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

    void write_to(std::ostream& os) const;
    void read_from(std::istream& is);

    friend ostream& operator<<(ostream& os, const List& l);
};
