#pragma once
#include <iostream>
#include "../mystring/mystring.hpp"
using namespace std;

struct Notification {
    enum Type {
        System,
        Message,
        Application
    };

    enum Priority {
        Default,
        Critical
    };

    struct SystemData {
        MyString text;
        Priority priority;
    };

    struct MessageData {
        MyString sender;
        MyString text;
    };

    struct ApplicationData {
        MyString app_name;
        MyString title;
        MyString body;
    };

    int timestamp;
    Type type;

    union Payload {
        SystemData system;
        MessageData message;
        ApplicationData application;

        Payload() {}
        ~Payload() {}
    } data;

    Notification();
    Notification(const Notification& other);
    ~Notification();

    Notification& operator=(const Notification& other);

    void copy_payload_from(const Notification& other);

    char get_type_rank() const;

    void print() const;
};

Notification create_system_notification(int timestamp, MyString text, Notification::Priority priority);
Notification create_message_notification(int timestamp, MyString sender, MyString text);
Notification create_application_notification(int timestamp, MyString app_name, MyString title, MyString body);

int count_notifications_by_type(Notification* notifications, int count, Notification::Type type);


class NotificationQueue {
private:
    Notification* notifications;
    int capacity;
    int queue_size;
    int first_index;
    int last_insert_index;

    void reserve(int new_capacity);
    void make_linear();

public:
    NotificationQueue();
    ~NotificationQueue();

    void push(const Notification& note);
    int get_size() const;

    Notification pop();
    Notification* begin();
    Notification* end();
};

class NotificationPriorityQueue {
private:
    Notification* notifications;
    int* push_indexes;

    int capacity;
    int queue_size;

    int next_push_index;

    void reserve(int new_capacity);
    void sift_up(int index);
    void sift_down(int index);
    bool is_better(int left_index, int right_index) const;

public:
    NotificationPriorityQueue();
    ~NotificationPriorityQueue();

    void push(const Notification& note);
    int get_size() const;
    Notification pop();
    Notification* begin();
    Notification* end();
};
