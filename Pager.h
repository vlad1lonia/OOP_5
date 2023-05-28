//
// Created by Vlad04 on 28.05.2023.
//

#ifndef OOP_5_COPIED_PAGER_H
#define OOP_5_COPIED_PAGER_H


#include "TreeNode.h"
class Pager : public TreeNode
{
private:
    int tick = 0;
    int number = 0;
    bool isBusy = false;
    int smLength = 0;
    std::string sendingMessage;
    std::vector<std::string> sentMessages;
    std::vector<std::string> receivedMessages;
public:
    Pager(TreeNode* head, std::string nodeName);
    std::string getStatus();
    int getNumber();
    void handleReceiveMessage(std::string message);
    void handleGetSentMessages(std::string message);
    void handleSendMessage(std::string message);
    void handleTick(std::string message);
    void sendMessageSignal(std::string& message);
    void sendSentMessagesSignal(std::string& message);
};


#endif //OOP_5_COPIED_PAGER_H
