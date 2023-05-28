//
// Created by Vlad04 on 28.05.2023.
//

#include "InputHandler.h"


InputHandler::InputHandler(ObjectsClass *head, string object_name) : ObjectsClass(head,
                                                                                  object_name) {}

void InputHandler::pager_addition_signal(string &message) {}

void InputHandler::enter_message_signal(string &message) {}

void InputHandler::show_tree_signal(string &message) {}

void InputHandler::tick_signal(string &message) {}

void InputHandler::pager_status_signal(string &message) {}

void InputHandler::app_class_status_signal(string &message) {}

void InputHandler::input_handler(string message) {

    string data;
    getline(cin, data);
    if (message == "PAGER") {
        if (data != "End of information about pagers")
            emit_command(SIGNAL_D(InputHandler::pager_addition_signal), data);
        else
            find_object_by_coordinate("/")->set_state(2);
    }
    if (message == "COMMAND") {
        if (data != "Turn off the system") {
            if (sent_count != 0 && data.rfind("Send a message") != 0) {
                tick++;
                emit_command(SIGNAL_D(InputHandler::tick_signal),
                             to_string(tick));
            }

            if (command_execution(data, "SHOWTREE")) {
                emit_command(SIGNAL_D(InputHandler::show_tree_signal), "SHOWTREE");
            } else if (command_execution(data, "Display the system status")) {
                emit_command(SIGNAL_D(InputHandler::app_class_status_signal), data);
            } else if (command_execution(data, "Display the pager status")) {
                emit_command(SIGNAL_D(InputHandler::pager_status_signal), data);
            }

            if (command_execution(data, "Send a message")) {
                emit_command(SIGNAL_D(InputHandler::enter_message_signal), data);
                sent_count++;
            } else {
                tick++; emit_command(SIGNAL_D(InputHandler::tick_signal), to_string(tick));
                sent_count = 0;
            }
        } else
            find_object_by_coordinate("/")->set_state(3);
    }
}

bool InputHandler::command_execution(string &data, string command) {
    if (data == command) {
        data = "";
        return true;
    }
    if (data.rfind(command) == 0) {
        data = data.substr(command.length() + 1);
        return true;
    }
    return false;
}
