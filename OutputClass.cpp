#include "OutputClass.h"


OutputClass::OutputClass(ObjectsClass* head_pointer, string object_name)
        : ObjectsClass(head_pointer, object_name) {}


// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

void OutputClass::output_signal(std::string &signal_text) { }

void OutputClass::output_handler(string handler_text) {

    ObjectsClass* root_object; root_object = find_object_by_coordinate("/");

    if (handler_text == "SHOWTREE") {
        cout << end_line; root_object->print_states(1);
        exit(0);
    }

    if (handler_text != "Ready to work") {
        cout << end_line;
    }

    cout << handler_text;
}