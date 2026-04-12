#include "list.hpp"
#include <iostream>
#include <fstream>
#include <cmath>

List::Node::Node() : m_Data(Circle()), pPrev(nullptr), pNext(nullptr) {}
List::Node::Node(const Circle& c) : m_Data(c), pPrev(nullptr), pNext(nullptr) {}

List::Iterator::Iterator(Node* node) : current(node) {}

const Circle& List::Iterator::operator*() const {
    return current->m_Data;
}

List::Iterator& List::Iterator::operator++() {
    current = current->pNext;
    return *this;
}

bool List::Iterator::operator==(const Iterator& other) const {
    return current == other.current;
}

bool List::Iterator::operator!=(const Iterator& other) const {
    return current != other.current;
}

List::Iterator List::begin() const {
    return Iterator(Head->pNext);
}

List::Iterator List::end() const {
    return Iterator(Tail);
}

void List::init_empty() {
    Head = new Node();
    Tail = new Node();
    Head->pNext = Tail;
    Tail->pPrev = Head;
    m_size = 0;
}

void List::copy_from(const List& other) {
    for (Node* current = other.Head->pNext; current != other.Tail; current = current->pNext) {
        push_back(current->m_Data);
    }
}

List::List() {
    init_empty();
}

List::~List() {
    clear();
    delete Head;
    delete Tail;
}

List::List(const List& other) {
    init_empty();
    copy_from(other);
}

List& List::operator=(const List& other) {
    if (this != &other) {
        clear();
        copy_from(other);
    }
    return *this;
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
        if (current->m_Data == c) {
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
    Node* current = Head->pNext;

    while (current != Tail) {
        Node* next = current->pNext;

        if (current->m_Data == c) {
            current->pPrev->pNext = current->pNext;
            current->pNext->pPrev = current->pPrev;
            delete current;
            m_size--;
            count++;
        }
        current = next;
    }

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

List::Node* List::split(Node* head) {
    Node* left = head;
    Node* right = head;

    while (right->pNext != Tail && right->pNext->pNext != Tail) {
        left = left->pNext;
        right = right->pNext->pNext;
    }

    Node* middle = left->pNext;
    left->pNext = Tail;
    Tail->pPrev = left;

    if (middle != Tail) {
        middle->pPrev = nullptr;
    }

    return middle;
}

List::Node* List::merge_sorted(Node* left, Node* right) {
    Node tmp;
    Node* t = &tmp;

    while (left != Tail && right != Tail) {
        if (left->m_Data.get_area() <= right->m_Data.get_area()) {
            t->pNext = left;
            left->pPrev = t;
            left = left->pNext;
        } else {
            t->pNext = right;
            right->pPrev = t;
            right = right->pNext;
        }

        t = t->pNext;
    }

    if (left != Tail) {
        t->pNext = left;
    } else {
        t->pNext = right;
    }

    return tmp.pNext;
}

List::Node* List::merge_sort(Node* head) {
    if (head == Tail || head->pNext == Tail) {
        return head;
    }

    Node* mid = split(head);
    Node* left = merge_sort(head);
    Node* right = merge_sort(mid);

    return merge_sorted(left, right);
}

void List::sort_by_area() {
    if (m_size < 2) return;

    Node* newHead = merge_sort(Head->pNext);

    Head->pNext = newHead;
    newHead->pPrev = Head;

    Node* current = Head->pNext;
    while (current->pNext != Tail) {
        current->pNext->pPrev = current;
        current = current->pNext;
    }

    current->pNext = Tail;
    Tail->pPrev = current;
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

void List::write_to(std::ostream& os) const {
    Node* current = Head->pNext;

    while (current != Tail) {
        os << current->m_Data << '\n';
        current = current->pNext;
    }
}

void List::read_from(std::istream& is) {
    clear();
    Circle c;

    while (is >> c) {
        push_back(c);
    }
}

ostream& operator<<(std::ostream& os, const List& l) {
    List::Node* current = l.Head->pNext;
    while (current != l.Tail) {
        os << current->m_Data << std::endl;
        current = current->pNext;
    }
    return os;
}
