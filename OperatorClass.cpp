#include "OperatorClass.h"


// Конструктор класса
OperatorClass::OperatorClass(ObjectsClass* head_pointer, string object_name)
        : ObjectsClass(head_pointer, object_name) { }

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

Message::Message(int sender_id, int receiver_id, std::string text) {
    this->sender_id = sender_id;
    this->receiver_id = receiver_id;
    this->text = text;
}

string OperatorClass::get_status() {

    string handler_count_string = to_string(messages_handler_count);
    string size_string = to_string(messages_queue.size());

    string status = "Operator " + handler_count_string + space + size_string;
    return status;
}

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

void OperatorClass::tick_handler(string handler_text) {

    if (!messages_queue.empty()) {

        tick = stoi(handler_text, nullptr, 10);
        Message* message = &messages_queue.front();

        string tick_string = to_string(tick);
        string receiver_string = to_string(message->receiver_id);
        string sender_string = to_string(message->sender_id);

        string command = tick_string + " Mail " + receiver_string
                         + space + sender_string + space + message->text;

        emit_command(SIGNAL_D(OperatorClass::send_signal), command);

        messages_handler_count++; messages_queue.pop();
    }
}

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

void OperatorClass::send_signal(string& signal_text) { }

void OperatorClass::send_handler(string handler_text) {

    int sender_id, receiver_id;
    string current_text;

    stringstream stream(handler_text);
    stream >> sender_id >> receiver_id; stream.ignore();

    getline(stream, current_text);

    string sender_string = to_string(sender_id);
    string receiver_string = to_string(receiver_id);

    string pager_string = "PAGER_" + receiver_string;
    ObjectsClass* pager_coordinate = find_object_by_coordinate(pager_string);

    if (pager_coordinate != nullptr) {
        messages_queue.emplace(sender_id, receiver_id, current_text);
    } else {
        string command = "Subscriber " + receiver_string + " not found";
        emit_command(SIGNAL_D(OperatorClass::send_error_signal), command);
    }
}

void OperatorClass::send_error_signal(string& error_text) { }