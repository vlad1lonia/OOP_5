//
// Created by Vlad04 on 28.05.2023.
//

#include "Operator.h"

Operator::Operator(ObjectsClass *head, string nodeName) : ObjectsClass(head, nodeName) {}

void Operator::send_signal(string &message) {}

void Operator::send_error(string &message) {}

void Operator::send_handler(string message) {

    string current_message;
    int sender, receiver;

    stringstream stream(message);
    stream >> sender >> receiver;
    stream.ignore();

    getline(stream, current_message);
    if (find_object_by_coordinate("PAGER_" + to_string(receiver)) != nullptr) {
        messages_queue.emplace(sender, receiver, current_message);
    } else {
        emit_command(SIGNAL_D(Operator::send_error), "Subscriber " +
                to_string(receiver) + " not found");
    }

}

void Operator::tick_handler(string message) {

    if (!messages_queue.empty()) {

        tick = stoi(message, nullptr, 10);
        Message *msg = &messages_queue.front();

        emit_command(SIGNAL_D(Operator::send_signal),
                     to_string(tick) + " Mail " + to_string(msg->receiver_id) + " "
                     + to_string(msg->sender_id) + " " + msg->text);

        messages_handler_count++;
        messages_queue.pop();
    }
}

string Operator::get_status() {
    return "Operator " + to_string(messages_handler_count) + " " +
           to_string(messages_queue.size());
}
