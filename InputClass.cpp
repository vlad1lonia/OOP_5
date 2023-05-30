#include "InputClass.h"


// Конструктор класса
InputClass::InputClass(ObjectsClass* head_pointer, string object_name)
        : ObjectsClass(head_pointer, object_name) {}

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

bool InputClass::command_execution(string& input, string command) {

    if (input == command) {
        input = ""; return true;
    } else if (input.rfind(command) == 0) {
        input = input.substr(command.length() + 1);
        return true;
    }

    return false;
}

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

void InputClass::input_handler(string handler_text) {

    string tick_string = to_string(tick);

    string show_tree_text = "SHOWTREE";

    string input; getline(cin, input);
    ObjectsClass* root_object = find_object_by_coordinate("/");

    if (handler_text == "PAGER" && input != "End of information about pagers") {
        emit_command(SIGNAL_D(InputClass::pager_addition_signal), input);
    } else {
        root_object->set_state(2);
    }

    if (handler_text == "COMMAND") {

        if (input != "Turn off the system") {

            if (sent_count != 0 && input.find("Send a message") != 0) {

                tick++; emit_command(SIGNAL_D(InputClass::tick_signal), tick_string);
            }

            if (command_execution(input, show_tree_text)) {
                emit_command(SIGNAL_D(InputClass::show_tree_signal), show_tree_text);
            } else if (command_execution(input, "Display the system status")) {
                emit_command(SIGNAL_D(InputClass::app_class_status_signal), input);
            } else if (command_execution(input, "Display the pager status")) {
                emit_command(SIGNAL_D(InputClass::pager_status_signal), input);
            }

            if (command_execution(input, "Send a message")) {
                emit_command(SIGNAL_D(InputClass::enter_message_signal), input);
                sent_count++;
            } else {
                tick++; sent_count = 0;
                tick_string = to_string(tick);
                emit_command(SIGNAL_D(InputClass::tick_signal), tick_string);
            }
        } else {
            root_object->set_state(3);
        }
    }
}

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

void InputClass::pager_addition_signal(string& signal_text) { }

void InputClass::pager_status_signal(string& signal_text) { }

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

void InputClass::app_class_status_signal(string& signal_text) { }

void InputClass::enter_message_signal(string& signal_text) { }

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

void InputClass::show_tree_signal(string& signal_text) { }

void InputClass::tick_signal(string& signal_text) { }