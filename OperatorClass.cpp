#include "OperatorClass.h"


// Конструктор класса
OperatorClass::OperatorClass(ObjectsClass* head_pointer, string object_name)
        : ObjectsClass(head_pointer, object_name) {}

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// Конструктор структуры Message
Message::Message(int sender_id, int receiver_id, string text) {
    this->sender_id = sender_id;
    this->receiver_id = receiver_id;
    this->text = text;
}

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// Метод получения статуса оператора
string OperatorClass::get_status() {

    string count_string = to_string(messages_handler_count);
    string size_string = to_string(messages_queue.size());

    string status = "Operator " + count_string + space + size_string;
    return status;
}

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// Метод обработчика такта оператора
void OperatorClass::tick_handler(string handler_text) {

    if (!messages_queue.empty()) {

        tick = stoi(handler_text);
        Message* message; message = &messages_queue.front();

        string tick_string = to_string(tick);
        string receiver_string = to_string(message->receiver_id);
        string sender_string = to_string(message->sender_id);

        string input = tick_string + " Mail " + receiver_string
                       + space + sender_string + space + message->text;

        emit_command(SIGNAL_D(OperatorClass::send_signal), input);

        messages_handler_count++; messages_queue.pop();
    }
}

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// Метод сигнала отправки сообщения
void OperatorClass::send_signal(string& signal_text) { }

// Метод обработчика отправки сообщения
void OperatorClass::send_handler(string handler_text) {

    int sender_id, receiver_id;
    string current_text;

    stringstream stream(handler_text);
    stream >> sender_id >> receiver_id; stream.ignore();

    getline(stream, current_text);

    string sender_string = to_string(sender_id);
    string receiver_string = to_string(receiver_id);

    string pager_string = "Pager " + receiver_string;
    ObjectsClass* pager_object; pager_object = find_object_by_coordinate(pager_string);

    if (pager_object != nullptr) {
        messages_queue.emplace(sender_id, receiver_id, current_text);
    } else {
        string input = "Subscriber " + receiver_string + " not found";
        emit_command(SIGNAL_D(OperatorClass::send_error_signal), input);
    }
}

// Метод сигнала ошибки
void OperatorClass::send_error_signal(string& error_text) { }