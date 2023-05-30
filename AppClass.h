//
// Created by Vlad04 on 28.05.2023.
//

#ifndef OOP_5_COPIED_APPCLASS_H
#define OOP_5_COPIED_APPCLASS_H


#include <map>
#include "ObjectsClass.h"
#include "InputClass.h"
#include "OperatorClass.h"
#include "OutputClass.h"
#include "PagerClass.h"

#define all(x) begin(x), end(x)

class AppClass : public ObjectsClass {

private:
    void addition_handler(string handler_text);
    void status_handler(string handler_text);

    void input_signal(string& signal_text);
    void message_signal(string& signal_text);

public:
    AppClass(ObjectsClass* head);

    void build();
    int execute();
};



#endif //OOP_5_COPIED_APPCLASS_H
