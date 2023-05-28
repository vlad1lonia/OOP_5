//
// Created by Vlad04 on 28.05.2023.
//

#ifndef OOP_5_COPIED_OUTPUTHANDLER_H
#define OOP_5_COPIED_OUTPUTHANDLER_H


#include "TreeNode.h"
class OutputHandler : public TreeNode {
public:
    OutputHandler(TreeNode* head, std::string nodeName);
    void handlePrintMessage(std::string message);
};


#endif //OOP_5_COPIED_OUTPUTHANDLER_H
