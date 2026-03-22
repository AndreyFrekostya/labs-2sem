#include "list.hpp"
#include <iostream>
#include <fstream>
#include <cmath>

List::Node::Node() : m_Data(Circle()), pPrev(nullptr), pNext(nullptr) {}
List::Node::Node(const Circle& c) : m_Data(c), pPrev(nullptr), pNext(nullptr) {}

List::List() {
    Head = new Node();
    Tail = new Node();
    Head->pNext = Tail;
    Tail->pPrev = Head;
    m_size = 0;
}

List::~List() {
    clear();
    delete Head;
    delete Tail;
}

void List::push_front(const Circle& c) {
    Node* newNode = new Node(c);
    newNode->pNext = Head->pNext;
    newNode->pPrev = Head;
    Head->pNext->pPrev = newNode;
    Head->pNext = newNode;
    m_size++;
}

void List::push_back(const Circle& c) {
    Node* newNode = new Node(c);
    newNode->pPrev = Tail->pPrev;
    newNode->pNext = Tail;
    Tail->pPrev->pNext = newNode;
    Tail->pPrev = newNode;
    m_size++;
}

bool List::remove_first(const Circle& c) {
    Node* current = Head->pNext;
    while (current != Tail) {
        if (std::abs(current->m_Data.get_radius() - c.get_radius()) < 1e-6 &&
            std::abs(current->m_Data.get_center().get_x() - c.get_center().get_x()) < 1e-6 &&
            std::abs(current->m_Data.get_center().get_y() - c.get_center().get_y()) < 1e-6) 
        {
            current->pPrev->pNext = current->pNext;
            current->pNext->pPrev = current->pPrev;
            delete current;
            m_size--;
            return true;
        }
        current = current->pNext;
    }
    return false;
}

size_t List::remove_all(const Circle& c) {
    size_t count = 0;
    while (remove_first(c)) count++;
    return count;
}

void List::clear() {
    Node* current = Head->pNext;
    while (current != Tail) {
        Node* tmp = current;
        current = current->pNext;
        delete tmp;
    }
    Head->pNext = Tail;
    Tail->pPrev = Head;
    m_size = 0;
}

size_t List::get_size() const { return m_size; }

void List::sort_by_area() {
    if (m_size < 2) return;

    for (Node* i = Head->pNext; i != Tail->pPrev; i = i->pNext) {
        for (Node* j = i->pNext; j != Tail; j = j->pNext) {
            if (i->m_Data.get_area() > j->m_Data.get_area()) {
                std::swap(i->m_Data, j->m_Data);
            }
        }
    }
}

void List::print() const {
    Node* current = Head->pNext;
    while (current != Tail) {
        current->m_Data.print();
        current = current->pNext;
    }
}

void List::print_to_file(const char* filename) const {
    std::ofstream fout(filename);
    if (!fout) return;
    Node* current = Head->pNext;
    while (current != Tail) {
        fout << current->m_Data << std::endl;
        current = current->pNext;
    }
    fout.close();
}

void List::read_from_file(const char* filename) {
    std::ifstream fin(filename);
    if (!fin) return;
    clear();
    Circle c;
    while (fin >> c) {
        push_back(c);
    }
    fin.close();
}

ostream& operator<<(std::ostream& os, const List& l) {
    List::Node* current = l.Head->pNext;
    while (current != l.Tail) {
        os << current->m_Data << std::endl;
        current = current->pNext;
    }
    return os;
}
