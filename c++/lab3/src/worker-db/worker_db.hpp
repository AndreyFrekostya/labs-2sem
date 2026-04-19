#pragma once
#include "../mystring/mystring.hpp"
#include "../worker-data/worker_data.hpp"

struct Node {
    MyString key;
    WorkerData worker;
    Node* next;

    Node(const MyString& k, const WorkerData& v);
};

class WorkerDbIterator {
private:
    Node** buckets;
    size_t buckets_count;
    size_t current_bucket;
    Node* current;

    void move_to_next_valid();

public:
    WorkerDbIterator();
    WorkerDbIterator(Node** _buckets, size_t _buckets_count, size_t _current_bucket, Node* _current);

    WorkerDbIterator& operator++();
    WorkerDbIterator operator++(int);

    WorkerData& operator*() const;
    WorkerData* operator->() const;

    const char* key() const;

    bool operator==(const WorkerDbIterator& other) const;
    bool operator!=(const WorkerDbIterator& other) const;
};

class WorkerDb {
private:
    Node** buckets;
    size_t buckets_count;

    size_t hash(const MyString& key) const;
    Node* findNode(const MyString& key, size_t bucket_index) const;

public:
    WorkerDb();
    ~WorkerDb();

    WorkerData& operator[](const MyString& surname);

    WorkerDbIterator begin() const;
    WorkerDbIterator end() const;
};

void print_db(WorkerDb& db);
double get_avg_age(WorkerDb& db);