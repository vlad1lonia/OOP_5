//
// Created by Vlad04 on 28.05.2023.
//

#include "Pager.h"

Pager::Pager(ObjectsClass *head_pointer, string object_name) :
                            ObjectsClass(head_pointer, "PAGER_" + object_name) {
    this->id = stoi(object_name, nullptr, 10);
}

string Pager::get_status() {
    return "Pager " + to_string(id) + space +
           to_string(sent_messages.size()) + space +
           to_string(received_messages.size());
}

int Pager::get_id() {
    return id;
}

void Pager::sender_signal(string &message) {}

void Pager::messages_data_signal(string &message) {}

void Pager::sender_handler(string message) {
    int sender, receiver;

    if (occupied) { return; }

    stringstream stream(message);
    string current_message;

    stream >> sender >> receiver;
    stream.ignore();

    getline(stream, current_message);
    if (sender == id) {
        pending_message = message;
        message_length = current_message.length();
        occupied = true;
    }

}

void Pager::receiver_handler(string message) {

    int sender, receiver, tick;
    string current_message;

    stringstream stream(message);
    stream >> tick >> current_message >> receiver >> sender;
    stream.ignore();

    getline(stream, current_message);
    if (receiver == id) {
        received_messages.push_back(to_string(tick) + space +
                                    to_string(sender) + space + current_message);
    }
}

void Pager::messages_data_handler(string message) {
    
    if (!occupied && stoi(message, nullptr, 10) == id) {

        string data_text = "The list of messages sent by the pager " +
                           to_string(id);
        for (int i = 0; i < sent_messages.size(); i++) {
            data_text += "\n" + sent_messages[i];
        }

        data_text += "\nList of received messages by the pager " +
                     to_string(id);

        for (int i = 0; i < received_messages.size(); i++) {
            data_text += "\n" + received_messages[i];
        }

        emit_command(SIGNAL_D(Pager::messages_data_signal), data_text);
    }
}

void Pager::tick_handler(string message) {

    int sender, receiver; string current_message;
    tick = stoi(message, nullptr, 10);

    if (!pending_message.empty() && occupied) {

        if (message_length <= 0) {

            stringstream stream(pending_message);
            stream >> sender >> receiver;
            stream.ignore();

            getline(stream, current_message);
            sent_messages.push_back(to_string(tick) + space +
                                    to_string(receiver) + space + current_message);
            emit_command(SIGNAL_D(Pager::sender_signal), pending_message);

            occupied = false; pending_message = "";
        }

        message_length -= 10;
    }
}
