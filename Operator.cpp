//
// Created by Vlad04 on 28.05.2023.
//

#include "Operator.h"

Operator::Operator(TreeNode* head, std::string nodeName) : TreeNode(head,
                                                                    nodeName) { }
void Operator::processSendMessageSignal(std::string& message) { }
void Operator::sendErrorMessage(std::string& message) { }
void Operator::handleSendMessage(std::string message)
{
    std::stringstream stream(message);
    std::string msg;
    int sender, receiver;
    stream >> sender >> receiver;
    stream.ignore();
    std::getline(stream, msg);
    if (findByPath("PAGER_" + std::to_string(receiver)) != nullptr)
        messagesQueue.push(Message(sender, receiver, msg));
    else
        emitSignal(AS_SIGNAL(Operator::sendErrorMessage), "Subscriber " +
                                                          std::to_string(receiver) + " not found");
}
void Operator::handleTick(std::string message)
{
    tick = std::stoi(message, nullptr, 10);
    if (messagesQueue.size() == 0)
        return;
    Message* msg = &messagesQueue.front();
    emitSignal(AS_SIGNAL(Operator::processSendMessageSignal),
               std::to_string(tick) + " Mail " + std::to_string(msg->receiver) + " "
               + std::to_string(msg->sender) + " " + msg->data);
    handledMessages++;
    messagesQueue.pop();
}
std::string Operator::getStatus()
{
    return "Operator " + std::to_string(handledMessages) + " " +
           std::to_string(messagesQueue.size());
}
