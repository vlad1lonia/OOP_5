#ifndef __OPERATORCLASS__H
#define __OPERATORCLASS__H


#include <queue>

#include "ObjectsClass.h"
#include "PagerClass.h"


// Структура сообщения
struct Message {

public:
    Message(int sender_id, int receiver_id, string text);

    int sender_id;   // Идентификатор (ID) пейджера-отправителя
    int receiver_id; // Идентификатор (ID) пейджера-получателя
    string text;     // Текст сообщения

};


class OperatorClass : public ObjectsClass {

private:
    int messages_handler_count = 0; // Количество обработанных сообщений
    int tick = 0;                   // Номер такта

    // Очередь из сообщений
    queue<Message> messages_queue;

public:
    // Констркутор класса
    OperatorClass(ObjectsClass* head_pointer, string object_name);

    string get_status(); // Метод получения состояния (статуса)

    void tick_handler(string handler_text); // Метод обработчика такта оператора

    void send_signal(string& signal_text);          // Метод сигнала пейджера
    void send_handler(string handler_text);         // Метод обработчика сообщения
    void send_error_signal(string& error_text);     // Метод сигнала ошибки поиска пейджера

};



#endif
