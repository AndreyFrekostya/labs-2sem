#include "notification.hpp"
#include <iostream>
#include <new>
using namespace std;

Notification::Notification(): timestamp(0), type(System) {
    new (&data.system) SystemData{MyString(), Default};
}

void Notification::copy_payload_from(const Notification& other) {
    switch (other.type) {
        case System:
            new (&data.system) SystemData{other.data.system.text, other.data.system.priority};
            break;
        case Message:
            new (&data.message) MessageData{other.data.message.sender, other.data.message.text};
            break;
        case Application:
            new (&data.application) ApplicationData{
                other.data.application.app_name,
                other.data.application.title,
                other.data.application.body
            };
            break;
    }
}

Notification::Notification(const Notification& other) {
    timestamp = other.timestamp;
    type = other.type;

    copy_payload_from(other);
}

Notification::~Notification() {
    if (type == System) {
        data.system.text.~MyString();
    } else if (type == Message) {
        data.message.sender.~MyString();
        data.message.text.~MyString();
    } else if (type == Application) {
        data.application.app_name.~MyString();
        data.application.title.~MyString();
        data.application.body.~MyString();
    }
}

Notification& Notification::operator=(const Notification& other) {
    if (this == &other)
        return *this;

    this->~Notification();

    timestamp = other.timestamp;
    type = other.type;

    copy_payload_from(other);

    return *this;
}

Notification create_system_notification(int timestamp, MyString text, Notification::Priority priority) {
    Notification notification;

    notification.timestamp = timestamp;
    notification.type = Notification::System;

    notification.data.system.text.~MyString();

    new (&notification.data.system) Notification::SystemData{text, priority};

    return notification;
}

Notification create_message_notification(int timestamp, MyString sender, MyString text) {
    Notification notification;

    notification.timestamp = timestamp;
    notification.type = Notification::Message;

    notification.data.system.text.~MyString();

    new (&notification.data.message) Notification::MessageData{sender, text};

    return notification;
}

Notification create_application_notification(int timestamp, MyString app_name, MyString title, MyString body) {
    Notification notification;

    notification.timestamp = timestamp;
    notification.type = Notification::Application;

    notification.data.system.text.~MyString();

    new (&notification.data.application) Notification::ApplicationData{app_name, title, body};

    return notification;
}

void Notification::print() const {
    int minutes = (timestamp / 60) % 60;
    int hours = (timestamp / 3600) % 24;

    cout << "(" << hours << ":" << minutes << ") ";
    if (type == System) {
        cout << "Системное уведомление: " << data.system.text.get_full_string() << '\n';
    } else if (type == Message) {
        cout << "Уведомление от отправителя: " << data.message.sender.get_full_string() << ". " << data.message.text.get_full_string() << '\n';
    } else {
        cout << "Уведомление от приложения: "
        << data.application.app_name.get_full_string()
        << ". "
        << data.application.title.get_full_string()
        << "; "
        << data.application.body.get_full_string()
        << '\n';
    }
}

char Notification::get_type_rank() const {
    if (type == Message) {
        return 3;
    }

    if (type == System) {
        return 2;
    }

    return 1;
}

int count_notifications_by_type(Notification* notifications, int count, Notification::Type type) {
    int result = 0;
    for (int i = 0; i < count; ++i) {
        if (notifications[i].type == type){
            result = result + 1;
        }
    }
    return result;
}

NotificationQueue::NotificationQueue(): notifications(nullptr), capacity(), queue_size(0), first_index(0), last_insert_index(0) {}

NotificationQueue::~NotificationQueue() {
    delete[] notifications;
}

void NotificationQueue::reserve(int new_capacity) {
    Notification* new_notifications = new Notification[new_capacity];

    for (int i = 0; i < queue_size; i = i + 1) {
        new_notifications[i] = notifications[(first_index + i) % capacity];
    }

    delete[] notifications;

    notifications = new_notifications;
    
    capacity = new_capacity;
    
    first_index = 0;
    last_insert_index = queue_size;
}

void NotificationQueue::make_linear() {
    if (queue_size == 0) {
        first_index = 0;
        last_insert_index = 0;
        return;
    }

    if (first_index < last_insert_index) {
        return;
    }

    Notification* new_notifications = new Notification[capacity];

    for (int i = 0; i < queue_size; i = i + 1) {
        new_notifications[i] = notifications[(first_index + i) % capacity];
    }

    delete[] notifications;

    notifications = new_notifications;

    first_index = 0;
    last_insert_index = queue_size;
}

void NotificationQueue::push(const Notification& note) {
    if (queue_size == capacity) {
        int new_capacity = capacity == 0 ? 2 : capacity * 2;
        reserve(new_capacity);
    }
   
    
    notifications[last_insert_index] = note;
    
    last_insert_index = (last_insert_index + 1) % capacity;
    
    queue_size = queue_size + 1;
}

int NotificationQueue::get_size() const {
    return queue_size;
}

Notification NotificationQueue::pop() {
    Notification result = notifications[first_index];

    first_index = (first_index + 1) % capacity;
    
    queue_size = queue_size - 1;

    if (queue_size == 0) {
        first_index = 0;
        last_insert_index = 0;
    }

    return result;
}

Notification* NotificationQueue::begin() {
    make_linear();
    return notifications;
}

Notification* NotificationQueue::end() {
    make_linear();
    return notifications + queue_size;
}

NotificationPriorityQueue::NotificationPriorityQueue():
    notifications(nullptr),
    push_indexes(nullptr),
    capacity(0),
    queue_size(0),
    next_push_index(0) {}

NotificationPriorityQueue::~NotificationPriorityQueue() {
    delete[] notifications;
    delete[] push_indexes;
}

void NotificationPriorityQueue::reserve(int new_capacity) {
    Notification* new_notifications = new Notification[new_capacity];
    int* new_push_indexes = new int[new_capacity];

    for (int i = 0; i < queue_size; i = i + 1) {
        new_notifications[i] = notifications[i];
        new_push_indexes[i] = push_indexes[i];
    }

    delete[] notifications;
    delete[] push_indexes;

    notifications = new_notifications;
    push_indexes = new_push_indexes;

    capacity = new_capacity;
}

bool NotificationPriorityQueue::is_better(int left_index, int right_index) const {
    const Notification& left = notifications[left_index];
    const Notification& right = notifications[right_index];

    bool left_is_critical_system = left.type == Notification::System && left.data.system.priority == Notification::Critical;
    bool right_is_critical_system = right.type == Notification::System && right.data.system.priority == Notification::Critical;

    if (left_is_critical_system != right_is_critical_system) {
        return left_is_critical_system;
    }

    if (left.timestamp != right.timestamp) {
        return left.timestamp < right.timestamp;
    }

    char left_type_rank = left.get_type_rank();
    char right_type_rank = right.get_type_rank();

    if (left_type_rank != right_type_rank) {
        return left_type_rank > right_type_rank;
    }

    return push_indexes[left_index] < push_indexes[right_index];
}

void NotificationPriorityQueue::sift_up(int index) {
    while (index > 0) {
        int parent_index = (index - 1) / 2;

        if (!is_better(index, parent_index)) {
            break;
        }

        Notification temp_notification = notifications[index];
        notifications[index] = notifications[parent_index];
        notifications[parent_index] = temp_notification;

        int temp_push_index = push_indexes[index];
        push_indexes[index] = push_indexes[parent_index];
        push_indexes[parent_index] = temp_push_index;

        index = parent_index;
    }
}

void NotificationPriorityQueue::sift_down(int index) {
    while (true) {
        int left_child = 2 * index + 1;
        int right_child = 2 * index + 2;
        int best_index = index;

        if (left_child < queue_size && is_better(left_child, best_index)) {
            best_index = left_child;
        }

        if (right_child < queue_size && is_better(right_child, best_index)) {
            best_index = right_child;
        }

        if (best_index == index) {
            break;
        }

        Notification temp_notification = notifications[index];
        notifications[index] = notifications[best_index];
        notifications[best_index] = temp_notification;

        int temp_push_index = push_indexes[index];
        push_indexes[index] = push_indexes[best_index];
        push_indexes[best_index] = temp_push_index;

        index = best_index;
    }
}

void NotificationPriorityQueue::push(const Notification& note) {
    if (queue_size == capacity) {
        int new_capacity = capacity == 0 ? 2 : capacity * 2;
        reserve(new_capacity);
    }

    notifications[queue_size] = note;
    push_indexes[queue_size] = next_push_index;

    next_push_index = next_push_index + 1;

    sift_up(queue_size);

    queue_size = queue_size + 1;
}

int NotificationPriorityQueue::get_size() const {
    return queue_size;
}

Notification NotificationPriorityQueue::pop() {
    Notification result = notifications[0];
    queue_size = queue_size - 1;

    if (queue_size > 0) {
        notifications[0] = notifications[queue_size];
        push_indexes[0] = push_indexes[queue_size];

        sift_down(0);
    }

    return result;
}

Notification* NotificationPriorityQueue::begin() {
    return notifications;
}

Notification* NotificationPriorityQueue::end() {
    return notifications + queue_size;
}