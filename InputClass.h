#ifndef __INPUTCLASS__H
#define __INPUTCLASS__H


#include "ObjectsClass.h"
#include "AppClass.h"

class InputClass : public ObjectsClass {

private:
    int sent_count = 0; // Количество отправленных сообщений
    int tick = 0;       // Номер такта

    // Метод проверки введённой команды
    bool command_execution(string& input, string command);

public:
    // Конструктор класса
    InputClass(ObjectsClass* head_pointer, string object_name);

    // Метод обработчика ввода команды
    void input_handler(string handler_text);

    void pager_addition_signal(string& signal_text);   // Метод сигнала добавления пейджера
    void pager_status_signal(string& signal_text);     // Метод сигнала полкчения статуса пейджера

    void app_class_status_signal(string& signal_text); // Метод сигнала получения статуса системы
    void enter_message_signal(string& signal_text);    // Метод сигнала ввода содержимого сообщения

    void show_tree_signal(string& signal_text);        // Метод сигнала вывода дерева иерархий
    void tick_signal(string& signal_text);             // Метод сигнала такта
};


#endif
