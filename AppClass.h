//
// Created by Vlad04 on 28.05.2023.
//

#ifndef OOP_5_COPIED_APPCLASS_H
#define OOP_5_COPIED_APPCLASS_H


#include <map>
#include "ObjectsClass.h"
#include "InputHandler.h"
#include "Operator.h"
#include "OutputHandler.h"
#include "Pager.h"

#define all(x) begin(x), end(x)

class AppClass : public ObjectsClass
{
public:
    AppClass(ObjectsClass* head);

    void build();
    int execute();

    void handlePagerAdd(string message);
    void handleGetSystemStatus(string message);
    void requireInputSignal(string& message);
    void printMessageSignal(string& message);
};



#endif //OOP_5_COPIED_APPCLASS_H
