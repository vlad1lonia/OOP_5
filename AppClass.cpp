//
// Created by Vlad04 on 28.05.2023.
//

#include "AppClass.h"

AppClass::AppClass(ObjectsClass *head) : ObjectsClass(head) { }

void AppClass::build() {

    set_object_name("SYSTEM");

    ObjectsClass *input_handler = new InputHandler(this, "INPUT_HANDLER");
    ObjectsClass *output_handler = new OutputHandler(this, "OUTPUT_HANDLER");
    ObjectsClass *operator_object = new Operator(this, "OPERATOR");

    set_state_for_all();

    set_connection( // Require input
            SIGNAL_D(AppClass::requireInputSignal),
            input_handler,
            HANDLER_D(InputHandler::input_handler)
    );
    set_connection( // Show message
            SIGNAL_D(AppClass::printMessageSignal),
            output_handler,
            HANDLER_D(OutputHandler::print_handler)
    );
    operator_object->set_connection( // Show message from Operator
            SIGNAL_D(Operator::send_error),
            output_handler,
            HANDLER_D(OutputHandler::print_handler)
    );
    input_handler->set_connection( // Add pager (to this)
            SIGNAL_D(InputHandler::pager_addition_signal),
            this,
            HANDLER_D(AppClass::handlePagerAdd)
    );
    input_handler->set_connection( // Handle show tree
            SIGNAL_D(InputHandler::show_tree_signal),
            output_handler,
            HANDLER_D(OutputHandler::print_handler)
    );
    input_handler->set_connection( // Handle get system status
            SIGNAL_D(InputHandler::app_class_status_signal),
            this,
            HANDLER_D(AppClass::handleGetSystemStatus)
    );

    while (get_state() != 2) {
        emit_command(SIGNAL_D(AppClass::requireInputSignal), "PAGER");
    }

    emit_command(SIGNAL_D(AppClass::printMessageSignal), "Ready to work");
}

int AppClass::execute() {

    set_state_for_all();
    while (get_state() != 3) {
        emit_command(SIGNAL_D(AppClass::requireInputSignal), "COMMAND");
    }

    emit_command(SIGNAL_D(AppClass::printMessageSignal), "Turn off the ATM");
    return EXIT_SUCCESS;
}

void AppClass::requireInputSignal(string &message) {}

void AppClass::printMessageSignal(string &message) {}

void AppClass::handlePagerAdd(string message) {

    ObjectsClass *operator_object = find_object_by_coordinate("/OPERATOR");
    ObjectsClass *input_handler = find_object_by_coordinate("/INPUT_HANDLER");
    ObjectsClass *output_handler = find_object_by_coordinate("/OUTPUT_HANDLER");

    Pager *pager = new Pager(find_object_by_coordinate("/OPERATOR"), message);

    operator_object->set_connection(SIGNAL_D(Operator::send_signal),
                                    pager, HANDLER_D(Pager::receiver_handler));
    
    pager->set_connection(SIGNAL_D(Pager::sender_signal),
                          operator_object, HANDLER_D(Operator::send_handler));
    pager->set_connection(SIGNAL_D(Pager::messages_data_signal),
                          output_handler, HANDLER_D(OutputHandler::print_handler));
    
    input_handler->set_connection(SIGNAL_D(InputHandler::tick_signal),
                                  operator_object, HANDLER_D(Operator::tick_handler));
    input_handler->set_connection(SIGNAL_D(InputHandler::tick_signal),
                                  pager, HANDLER_D(Pager::tick_handler));
    
    input_handler->set_connection(SIGNAL_D(InputHandler::enter_message_signal),
                                  pager, HANDLER_D(Pager::sender_handler));
    input_handler->set_connection(SIGNAL_D(InputHandler::pager_status_signal),
                                  pager, HANDLER_D(Pager::messages_data_handler));

}

void AppClass::handleGetSystemStatus(string message) {
    
    Operator *operator_pointer = (Operator *) 
            find_object_by_coordinate("/OPERATOR");
    string status_string; vector<Pager*> pagers;
    
    for (int index = 0; index < operator_pointer->get_class_objects().size(); index++) {
        pagers.push_back((Pager *)
        operator_pointer->get_class_objects()[index]);
    }
    
    while (!pagers.empty()) {
        
        int required_pager_id = INT32_MAX;
        Pager *pager = nullptr;
        
        for (int index = 0; index < pagers.size(); index++) {
            int pager_id = pagers[index]->get_id();
            
            if (pager_id < required_pager_id) {
                pager = pagers[index];
                required_pager_id = pager_id;
            }
        }

        status_string += pager->get_status() + "\n";
        pagers.erase(find(all(pagers), pager));

    }

    status_string += operator_pointer->get_status();
    emit_command(SIGNAL_D(AppClass::printMessageSignal), status_string);
}