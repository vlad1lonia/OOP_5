//
// Created by Vlad04 on 28.05.2023.
//

#include "OutputHandler.h"

OutputHandler::OutputHandler(ObjectsClass* head, string nodeName) :
        ObjectsClass(head, nodeName) { }

void OutputHandler::print_handler(string message) {

    ObjectsClass* head_object = find_object_by_coordinate("/");

    if (message == "SHOWTREE") {
        cout << end_line;
        head_object->print_states(1);
        exit(0);
    }

    cout << (message == "Ready to work" ? "" : "\n") << message;
}
