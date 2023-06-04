#include "InputClass.h"


// Конструктор класса
InputClass::InputClass(ObjectsClass* head_pointer, string object_name)
        : ObjectsClass(head_pointer, object_name) {}

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// Метод проверки введённой команды
bool InputClass::command_execution(string& input, string command) {

    if (input == command) {
        input = ""; return true;
    } else if (input.find(command) == 0) {
        input = input.substr(command.length() + 1);
        return true;
    }

    return false;
}

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// Метод обработчика ввода команды
void InputClass::input_handler(string handler_text) {

    ObjectsClass* root_object; root_object = find_object_by_coordinate("/");
    string tick_string = to_string(tick);

    string show_tree_text = "SHOWTREE";
    string end_info_text = "End of information about pagers";
    string off_text = "Turn off the system";
    string system_status = "Display the system status";
    string pager_status = "Display the pager status";

    string input; getline(cin, input);

    if (handler_text == "Pager" && input != end_info_text) {
        emit_command(SIGNAL_D(InputClass::pager_addition_signal), input);
    } else {
        root_object->set_state(2);
    }

    if (handler_text == "Command") {

        if (input != off_text) {

            int find_string = input.find("Send a message");

            if (sent_count != 0 && find_string != 0) {

                tick++; emit_command(SIGNAL_D(InputClass::tick_signal), tick_string);
            }

            if (command_execution(input, show_tree_text)) {
                emit_command(SIGNAL_D(InputClass::show_tree_signal), show_tree_text);
            } else if (command_execution(input, system_status)) {
                emit_command(SIGNAL_D(InputClass::app_class_status_signal), input);
            } else if (command_execution(input, pager_status)) {
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

// Метод сигнала добавлени пейджера
void InputClass::pager_addition_signal(string& signal_text) { }

// Метод сигнала получения статуса пейджера
void InputClass::pager_status_signal(string& signal_text) { }

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// Метод сигнала получения статуса пейджера
void InputClass::app_class_status_signal(string& signal_text) { }

// Метод сигнала ввода содержимого сообщения
void InputClass::enter_message_signal(string& signal_text) { }

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// Метод сигнала вывода дерева иерархий
void InputClass::show_tree_signal(string& signal_text) { }

// Метод такта сигнала
void InputClass::tick_signal(string& signal_text) { }