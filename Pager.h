//
// Created by Vlad04 on 28.05.2023.
//

#ifndef OOP_5_COPIED_PAGER_H
#define OOP_5_COPIED_PAGER_H


#include "ObjectsClass.h"
class Pager : public ObjectsClass {

private:
    int tick = 0; // Номер такта
    int id = 0;   // Идентификатор (ID) пейджера

    // Состояние занятости пейджера (true - занят, false - свободен)
    bool occupied = false;
    int message_length = 0; // Длина сообщение

    string pending_message;           // Отправляющееся сообщение
    vector<string> sent_messages;     // Контейнер отправленных сообщений
    vector<string> received_messages; // Контейнер полученных сообщений
    
public:
    Pager(ObjectsClass* head_pointer, string object_name);

    string get_status(); // Метод получения "Статуса" пейджера
    int get_id();        // Метод получения идентификатора (ID) пейджера

    void receiver_handler(string message);
    void tick_handler(string message);

    void sender_signal(string& message);
    void sender_handler(string message);

    void messages_data_signal(string& message);
    void messages_data_handler(string message);
};


#endif //OOP_5_COPIED_PAGER_H
