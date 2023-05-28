//
// Created by Vlad04 on 28.05.2023.
//

#ifndef OOP_5_COPIED_OPERATOR_H
#define OOP_5_COPIED_OPERATOR_H


#include "ObjectsClass.h"
#include "Pager.h"
#include <queue>


struct Message {
public:
    string text;
    int receiver_id;
    int sender_id;

    Message(int sender_id, int receiver_id, string text) {
        this->sender_id = sender_id;
        this->receiver_id = receiver_id;
        this->text = text;
    }
};

class Operator : public ObjectsClass {

private:
    queue<Message> messages_queue;
    int messages_handler_count = 0;
    int tick = 0;

public:
    Operator(ObjectsClass *head, string nodeName);

    string get_status();

    void send_signal(string &message);
    void send_handler(string message);

    void send_error(string &message);
    void tick_handler(string message);
};


#endif //OOP_5_COPIED_OPERATOR_H
