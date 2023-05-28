//
// Created by Vlad04 on 28.05.2023.
//

#include "Pager.h"

Pager::Pager(TreeNode* head, std::string number) : TreeNode(head, "PAGER_" +
                                                                  number)
{
    this->number = std::stoi(number, nullptr, 10);
}
std::string Pager::getStatus()
{
    return "Pager " + std::to_string(number) + " " +
           std::to_string(sentMessages.size()) + " " +
           std::to_string(receivedMessages.size());
}
int Pager::getNumber()
{
    return number;
}
void Pager::sendMessageSignal(std::string& message) { }
void Pager::sendSentMessagesSignal(std::string& message) { }
void Pager::handleSendMessage(std::string message)
{
    if (isBusy)
        return;
    std::stringstream stream(message);
    int sender, receiver;
    std::string msg;
    stream >> sender >> receiver;
    stream.ignore();
    std::getline(stream, msg);
    if (sender == number)
    {
        sendingMessage = message;
        smLength = msg.length();
        isBusy = true;
    }
}
void Pager::handleReceiveMessage(std::string message)
{
std::stringstream stream(message);
int sender, receiver, tick;
std::string msg;
stream >> tick >> msg >> receiver >> sender;
stream.ignore();
std::getline(stream, msg);
if (receiver == number)
receivedMessages.push_back(std::to_string(tick) + " " +
std::to_string(sender) + " " + msg);
}
void Pager::handleGetSentMessages(std::string message)
{
    if (isBusy || stoi(message, nullptr, 10) != number)
        return;
    std::string toSend = "The list of messages sent by the pager " +
                         std::to_string(number);
    for (int i = 0; i < sentMessages.size(); i++)
        toSend += "\n" + sentMessages[i];
    toSend += "\nList of received messages by the pager " +
              std::to_string(number);
    for (int i = 0; i < receivedMessages.size(); i++)
        toSend += "\n" + receivedMessages[i];
    emitSignal(AS_SIGNAL(Pager::sendSentMessagesSignal), toSend);
}
void Pager::handleTick(std::string message)
{
    tick = std::stoi(message, nullptr, 10);
    if (sendingMessage != "" && isBusy)
    {
        if (smLength <= 0)
        {
            std::stringstream stream(sendingMessage);
            int sender, receiver;
            std::string msg;
            stream >> sender >> receiver;
            stream.ignore();
            std::getline(stream, msg);
            sentMessages.push_back(std::to_string(tick) + " " +
                                   std::to_string(receiver) + " " + msg);
            emitSignal(AS_SIGNAL(Pager::sendMessageSignal), sendingMessage);
            isBusy = false;
            sendingMessage = "";
        }
        smLength -= 10;
    }
}
