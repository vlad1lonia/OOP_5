#include "AppClass.h"

#include <iostream>

#define end_line '\n'
#define quintuple_space "     "
#define space ' '
#define slash '/'

using namespace std;

// Параметризированный конструктор класса
AppClass::AppClass(ObjectsClass* root_pointer) : ObjectsClass(root_pointer) {}

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// Метод построения дерева иерархий объектов
void AppClass::build() {

    string pager_text = "Pager";
    string ready_to_work_text = "Ready to work";

    // Установление имени для корневого объекта
    set_object_name("System");

    // Добавление объектов в дерево иерархий
    ObjectsClass* input_object = new InputClass(this, "Input");
    ObjectsClass* output_object = new OutputClass(this, "Output");
    ObjectsClass* operator_object = new OperatorClass(this, "Operator");

    // Изменение состояния готовности всех объектов на состояние "ready"
    set_state_for_all();

    // Блок установления связей

    // Пользовательский ввод
    set_connection(SIGNAL_D(AppClass::input_signal),
                   input_object, HANDLER_D(InputClass::input_handler));

    // Показ содержимиого сообщения
    set_connection(SIGNAL_D(AppClass::message_signal),
                   output_object, HANDLER_D(OutputClass::output_handler));

    // Показ информации от оператора
    operator_object->set_connection(SIGNAL_D(OperatorClass::send_error_signal),
                                    output_object, HANDLER_D(OutputClass::output_handler));

    // Добавление нового пейджера в систему
    input_object->set_connection(SIGNAL_D(InputClass::pager_addition_signal),
                                 this, HANDLER_D(AppClass::addition_handler));

    // Показ дерева иерархий
    input_object->set_connection(SIGNAL_D(InputClass::show_tree_signal),
                                 output_object, HANDLER_D(OutputClass::output_handler));

    // Показ состояния (статуса) системы
    input_object->set_connection(SIGNAL_D(InputClass::app_class_status_signal),
                                 this, HANDLER_D(AppClass::status_handler));

    int current_state = get_state();
    while (current_state != 2) {


        emit_command(SIGNAL_D(AppClass::input_signal), pager_text);
        current_state = get_state();
    }

    // Выдача сигнала об окончании загрузки данных и построения дерева иерархий объектов
    emit_command(SIGNAL_D(AppClass::message_signal), ready_to_work_text);
}

// Метод запуска консольного приложения (программы)
int AppClass::execute() {

    string command_string = "Command";
    string turn_off_string = "Turn off the ATM";

    set_state_for_all();

    int current_state = get_state();
    while (current_state != 3) {
        emit_command(SIGNAL_D(AppClass::input_signal), command_string);
        current_state = get_state();
    }

    // Выдача сигнала об окончании работы системы
    emit_command(SIGNAL_D(AppClass::message_signal), turn_off_string);

    return EXIT_SUCCESS;
}

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// Метод обработчика добавления пейджера
void AppClass::addition_handler(string handler_text) {

    ObjectsClass* input_object; input_object = find_object_by_coordinate("/Input");
    ObjectsClass* output_object; output_object = find_object_by_coordinate("/Output");
    ObjectsClass* operator_object; operator_object = find_object_by_coordinate("/Operator");

    PagerClass* pager = new PagerClass(operator_object, handler_text);

    // Блок установления связей

    operator_object->set_connection(SIGNAL_D(OperatorClass::send_signal),
                                    pager, HANDLER_D(PagerClass::receiver_handler));

    pager->set_connection(SIGNAL_D(PagerClass::sender_signal),
                          operator_object, HANDLER_D(OperatorClass::send_handler));
    pager->set_connection(SIGNAL_D(PagerClass::messages_data_signal),
                          output_object, HANDLER_D(OutputClass::output_handler));

    input_object->set_connection(SIGNAL_D(InputClass::tick_signal),
                                 operator_object, HANDLER_D(OperatorClass::tick_handler));
    input_object->set_connection(SIGNAL_D(InputClass::tick_signal),
                                 pager, HANDLER_D(PagerClass::tick_handler));


    input_object->set_connection(SIGNAL_D(InputClass::enter_message_signal),
                                 pager, HANDLER_D(PagerClass::sender_handler));
    input_object->set_connection(SIGNAL_D(InputClass::pager_status_signal),
                                 pager, HANDLER_D(PagerClass::messages_data_handler));

}

// Метод обработчика сбора информации и её выдачи
void AppClass::status_handler(string handler_text) {

    OperatorClass* operator_object = (OperatorClass*) find_object_by_coordinate("/Operator");
    vector<ObjectsClass*> local_class_objects = operator_object->get_class_objects();

    string status_string; vector<PagerClass*> pagers;

    for (int index = 0; index < local_class_objects.size(); index++) {
        PagerClass* local_pager; local_pager =(PagerClass*) local_class_objects[index];
        pagers.push_back(local_pager);
    }

    while (!pagers.empty()) {

        int required_id = INT32_MAX;
        PagerClass* pager = nullptr;

        for (int index = 0; index < pagers.size(); index++) {
            int pager_id = pagers[index]->get_id();

            if (pager_id < required_id) {
                pager = pagers[index];
                required_id = pager_id;
            }
        }

        status_string += pager->get_status() + "\n";
        pagers.erase(find(all(pagers), pager));
    }

    status_string += operator_object->get_status();
    emit_command(SIGNAL_D(AppClass::message_signal), status_string);

}

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// Метод сигнала запроса пользовательского ввода
void AppClass::input_signal(string& signal_text) { }

// Метод сигнала вывода содержимого сообщения
void AppClass::message_signal(string& signal_text) { }