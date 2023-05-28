//
// Created by Vlad04 on 28.05.2023.
//

#ifndef OOP_5_COPIED_OUTPUTHANDLER_H
#define OOP_5_COPIED_OUTPUTHANDLER_H


#include "ObjectsClass.h"
class OutputHandler : public ObjectsClass {
public:
    OutputHandler(ObjectsClass* head, string nodeName);
    void print_handler(string message);
};


#endif //OOP_5_COPIED_OUTPUTHANDLER_H
