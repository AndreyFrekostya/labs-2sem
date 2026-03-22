#include <cassert>
#include <iostream>
#include "../src/notification/notification.hpp"

int main() {
    NotificationPriorityQueue queue;

    Notification app = create_application_notification(1, "app", "title", "body");
    Notification msg1 = create_message_notification(1, "andrey", "hello");
    Notification sys_default = create_system_notification(1, "system default", Notification::Default);
    Notification sys_critical = create_system_notification(1, "system critical", Notification::Critical);
    Notification msg2 = create_message_notification(1, "andrey2", "hello");

    queue.push(app);
    queue.push(msg1);
    queue.push(sys_default);
    queue.push(sys_critical);
    queue.push(msg2);

    Notification first = queue.pop();
    assert(first.type == Notification::System);
    assert(first.data.system.priority == Notification::Critical);

    Notification second = queue.pop();
    assert(second.type == Notification::Message);
    assert(second.data.message.sender == MyString("andrey"));

    Notification third = queue.pop();
    assert(third.type == Notification::Message);
    assert(third.data.message.sender == MyString("andrey2"));

    Notification fourth = queue.pop();
    assert(fourth.type == Notification::System);
    assert(fourth.data.system.priority == Notification::Default);

    Notification fifth = queue.pop();
    assert(fifth.type == Notification::Application);

    std::cout << "Тест NotificationPriorityQueue пройден\n";
    return 0;
}