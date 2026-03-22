#include "worker_db.hpp"
using namespace std;

Node::Node(const MyString& k, const WorkerData& v):
    key(k), worker(v), next(nullptr) {}

WorkerDb::WorkerDb(): buckets(nullptr), buckets_count(127) {
    buckets = new Node*[buckets_count];

    for (size_t i = 0; i < buckets_count; i++) {
        buckets[i] = nullptr;
    }
}

WorkerDb::~WorkerDb() {
    for (size_t i = 0; i < buckets_count; i++) {
        Node* current = buckets[i];

        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    delete[] buckets;
}

size_t WorkerDb::hash(const MyString& key) const {
    const char* str = key.get_full_string();
    size_t result = 0;

    while (*str != '\0') {
        result = result * 37 + *str;
        str++;
    }

    return result % buckets_count;
}

Node* WorkerDb::findNode(const MyString& key, size_t bucket_index) const {
    Node* current = buckets[bucket_index];

    while (current != nullptr) {
        if (current->key == key) {
            return current;
        }

        current = current->next;
    }

    return nullptr;
}

WorkerData& WorkerDb::operator[](const MyString& surname){
    size_t bucket_index = hash(surname);
    Node* foundedNode = findNode(surname, bucket_index);

    if (foundedNode != nullptr) {
        return foundedNode->worker;
    }

    Node* newNode = new Node(surname, WorkerData());

    newNode->next = buckets[bucket_index];
    buckets[bucket_index] = newNode;

    return newNode->worker;
}

WorkerDbIterator::WorkerDbIterator():
    buckets(nullptr), buckets_count(0), current_bucket(0), current(nullptr) {}

WorkerDbIterator::WorkerDbIterator(Node** _buckets, size_t _buckets_count, size_t _current_bucket, Node* _current):
    buckets(_buckets), buckets_count(_buckets_count), current_bucket(_current_bucket), current(_current) {}

void WorkerDbIterator::move_to_next_valid() {
    while (current == nullptr && current_bucket < buckets_count) {
        current = buckets[current_bucket];

        if (current == nullptr) {
            current_bucket++;
        }
    }
}

WorkerDbIterator& WorkerDbIterator::operator++() {
    if (current != nullptr) {
        current = current->next;
    }

    if (current == nullptr) {
        current_bucket++;
        move_to_next_valid();
    }

    return *this;
}

WorkerDbIterator WorkerDbIterator::operator++(int) {
    WorkerDbIterator temp = *this;
    ++(*this);
    return temp;
}

WorkerData& WorkerDbIterator::operator*() const {
    if (!current) {
        throw;
    }

    return current->worker;
}

WorkerData* WorkerDbIterator::operator->() const {
    if (!current) {
        return nullptr;
    }

    return &current->worker;
}

const char* WorkerDbIterator::key() const {
    if (!current) {
        return "";
    }

    return current->key.get_full_string();
}

bool WorkerDbIterator::operator==(const WorkerDbIterator& other) const {
    return current == other.current &&
           current_bucket == other.current_bucket &&
           buckets == other.buckets;
}

bool WorkerDbIterator::operator!=(const WorkerDbIterator& other) const {
    return !(*this == other);
}

WorkerDbIterator WorkerDb::begin() const {
    size_t bucket_index = 0;
    Node* current = nullptr;

    while (bucket_index < buckets_count && buckets[bucket_index] == nullptr) {
        bucket_index++;
    }

    if (bucket_index < buckets_count) {
        current = buckets[bucket_index];
    }

    return WorkerDbIterator(buckets, buckets_count, bucket_index, current);
}

WorkerDbIterator WorkerDb::end() const {
    return WorkerDbIterator(buckets, buckets_count, buckets_count, nullptr);
}

void print_db(WorkerDb& db) {
    for (auto it = db.begin(); it != db.end(); ++it){
        std::cout << it.key() << " -> " << it->get_name() << '\n';
    }
}

double get_avg_age(WorkerDb& db){
    double sum_ages = 0;
    size_t count = 0;

    for (auto it = db.begin(); it != db.end(); ++it){
        count++;
        sum_ages += it->get_age();
    }

    if (count == 0) {
        return 0;
    }

    return static_cast<double>(sum_ages / count);
}