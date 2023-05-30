//
// Created by Vlad04 on 28.05.2023.
//

#ifndef OOP_5_COPIED_OUTPUTCLASS_H
#define OOP_5_COPIED_OUTPUTCLASS_H


#include "ObjectsClass.h"


class OutputClass : public ObjectsClass {
public:
    OutputClass(ObjectsClass* head_pointer, string object_name);
    void print_handler(string message);
};


#endif //OOP_5_COPIED_OUTPUTCLASS_H
