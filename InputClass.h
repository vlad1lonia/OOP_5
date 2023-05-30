//
// Created by Vlad04 on 28.05.2023.
//

#ifndef OOP_5_COPIED_INPUTCLASS_H
#define OOP_5_COPIED_INPUTCLASS_H


#include "ObjectsClass.h"
#include "AppClass.h"

class InputClass : public ObjectsClass {

private:
    int sent_count = 0; // Количество отправленных сообщений
    int tick = 0;       // Номер такта

    bool command_execution(string& input, string command); // Метод запуска команды

public:
    // Конструктор класса
    InputClass(ObjectsClass* head_pointer, string object_name);

    void input_handler(string handler_text);

    void pager_addition_signal(string& signal_text);
    void pager_status_signal(string& signal_text);

    void app_class_status_signal(string& signal_text);
    void enter_message_signal(string& signal_text);

    void show_tree_signal(string& signal_text);
    void tick_signal(string& signal_text);
};

#endif //OOP_5_COPIED_INPUTCLASS_H
