//
// Created by Vlad04 on 28.05.2023.
//

#ifndef OOP_5_COPIED_SYSTEM_H
#define OOP_5_COPIED_SYSTEM_H


#include <map>
#include "TreeNode.h"
#include "InputHandler.h"
#include "Operator.h"
#include "OutputHandler.h"
#include "Pager.h"

class System : public TreeNode
{
public:
    System(TreeNode* head);
    void build();
    int run();
    void handlePagerAdd(std::string message);
    void handleGetSystemStatus(std::string message);
    void requireInputSignal(std::string& message);
    void printMessageSignal(std::string& message);
};



#endif //OOP_5_COPIED_SYSTEM_H
