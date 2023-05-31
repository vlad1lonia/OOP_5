#include "PagerClass.h"


// Конструктор класса
PagerClass::PagerClass(ObjectsClass* head_pointer, string object_name)
        : ObjectsClass(head_pointer, "Pager " + object_name) {

    int converted_id = stoi(object_name);
    this->id = converted_id;
}

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// Метод получения состояния (статуса) пейджера
string PagerClass::get_status() {

    string string_id = to_string(id);
    string sent_size_string = to_string(sent_messages.size());
    string received_size_string = to_string(received_messages.size());

    string status = "Pager " + string_id + space +
                    sent_size_string + space + received_size_string;

    return status;
}

// Метод получения идентификатора (ID) пейлжера
int PagerClass::get_id() {
    return id;
}

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

void PagerClass::receiver_handler(string handler_text) {

    int sender_id, receiver_id, tick;
    string current_text, tick_string, sender_id_string;

    stringstream stream(handler_text);

    stream >> tick >> current_text >> receiver_id >> sender_id;
    stream.ignore(); getline(stream, current_text);

    if (receiver_id == id) {
        tick_string = to_string(tick);
        sender_id_string = to_string(sender_id);

        received_messages.push_back(tick_string + space +
                                    sender_id_string + space + current_text);
    }
}

void PagerClass::tick_handler(string handler_text) {

    int sender_id, receiver_id;
    string current_text, tick_string, receiver_id_string;

    tick = stoi(handler_text);
    tick_string = to_string(tick);

    stringstream stream(pending_message);
    stream >> sender_id >> receiver_id; stream.ignore();
    receiver_id_string = to_string(receiver_id);

    getline(stream, current_text);

    if (!pending_message.empty() && occupied) {

        if (message_length <= 0) {

            sent_messages.push_back(tick_string + space
                                    + receiver_id_string + space + current_text);

            emit_command(SIGNAL_D(PagerClass::sender_signal), pending_message);
            occupied = false; pending_message = "";
        }

        message_length -= 10;
    }
}

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

void PagerClass::sender_signal(string& signal_text) { }

void PagerClass::sender_handler(string handler_text) {

    if (occupied) { return; }

    int sender_id, receiver_id;
    string current_text;

    stringstream stream(handler_text);
    stream >> sender_id >> receiver_id;

    stream.ignore(); getline(stream, current_text);

    if (sender_id == id) {

        pending_message = handler_text;
        message_length = current_text.length();
        occupied = true;
    }

}

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

void PagerClass::messages_data_signal(string& signal_text) { };

void PagerClass::messages_data_handler(string handler_text) {

    string id_string = to_string(id);
    string data_text;
    int converted_text = stoi(handler_text);

    if (!occupied && converted_text == id) {

        data_text = "The list of messages sent by the pager " + id_string;
        for (int index = 0; index < sent_messages.size(); index++) {
            data_text += "\n" + sent_messages[index];
        }

        data_text += "\nList of received messages by the pager " + id_string;
        for (int index = 0; index < received_messages.size(); index++) {
            data_text += "\n" + received_messages[index];
        }

        emit_command(SIGNAL_D(PagerClass::messages_data_signal), data_text);
    }
}