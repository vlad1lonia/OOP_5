//
// Created by Vlad04 on 28.05.2023.
//

#ifndef OOP_5_COPIED_INPUTHANDLER_H
#define OOP_5_COPIED_INPUTHANDLER_H


#include "TreeNode.h"
#include "System.h"

class InputHandler : public TreeNode
{
private:
    int prevSent = 0;
    int tick = 0;
    bool tryParseCMD(std::string& data, std::string cmd);
public:
    InputHandler(TreeNode* head, std::string nodeName);
    void handleRequireInput(std::string message);
    void addPagerSignal(std::string& message);
    void onSendMessageSignal(std::string& message);
    void onShowTreeSignal(std::string& message);
    void onTickSignal(std::string& message);
    void onGetPagerStatusSignal(std::string& message);
    void onGetSystemStatusSignal(std::string& message);
};


#endif //OOP_5_COPIED_INPUTHANDLER_H
