//
// Created by Vlad04 on 28.05.2023.
//

#ifndef OOP_5_COPIED_OPERATOR_H
#define OOP_5_COPIED_OPERATOR_H


#include "TreeNode.h"
#include "Pager.h"
#include <queue>
struct Message
{
    std::string data;
    int receiver;
    int sender;
    Message(int sender, int receiver, std::string data)
    {
        this->sender = sender;
        this->receiver = receiver;
        this->data = data;
    }
};
class Operator : public TreeNode
{
private:
    std::queue<Message> messagesQueue;
    int handledMessages = 0;
    int tick = 0;
public:
    Operator(TreeNode* head, std::string nodeName);
    std::string getStatus();
    void processSendMessageSignal(std::string& message);
    void sendErrorMessage(std::string& message);
    void handleSendMessage(std::string message);
    void handleTick(std::string message);
};


#endif //OOP_5_COPIED_OPERATOR_H
