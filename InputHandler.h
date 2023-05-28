//
// Created by Vlad04 on 28.05.2023.
//

#ifndef OOP_5_COPIED_INPUTHANDLER_H
#define OOP_5_COPIED_INPUTHANDLER_H


#include "ObjectsClass.h"
#include "AppClass.h"

class InputHandler : public ObjectsClass {

private:
    int sent_count = 0;
    int tick = 0;
    bool command_execution(string& data, string command);

public:
    InputHandler(ObjectsClass* head, string object_name);
    void input_handler(string message);

    void pager_addition_signal(string& message);
    void pager_status_signal(string& message);

    void app_class_status_signal(string& message);
    void enter_message_signal(string& message);

    void show_tree_signal(string& message);
    void tick_signal(string& message);
};


#endif //OOP_5_COPIED_INPUTHANDLER_H
