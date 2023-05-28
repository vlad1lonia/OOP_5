//
// Created by Vlad04 on 28.05.2023.
//

#include "OutputHandler.h"

OutputHandler::OutputHandler(TreeNode* head, std::string nodeName) :
        TreeNode(head, nodeName) { }

void OutputHandler::handlePrintMessage(std::string message)
{
    if (message == "SHOWTREE")
    {
        std::cout << std::endl;
        findByPath("/")->printBranch(true);
        exit(0);
    }
    std::cout << (message == "Ready to work" ? "" : "\n") << message;
}
