//
// Created by Vlad04 on 28.05.2023.
//

#include "InputHandler.h"


InputHandler::InputHandler(TreeNode* head, std::string nodeName) : TreeNode(head,
                                                                            nodeName) { }
void InputHandler::addPagerSignal(std::string& message) { }
void InputHandler::onSendMessageSignal(std::string& message) { }
void InputHandler::onShowTreeSignal(std::string& message) { }
void InputHandler::onTickSignal(std::string& message) { }
void InputHandler::onGetPagerStatusSignal(std::string& message) { }
void InputHandler::onGetSystemStatusSignal(std::string& message) { }
void InputHandler::handleRequireInput(std::string message)
{
    std::string data;
    std::getline(std::cin, data);
    if (message == "PAGER")
    {
        if (data != "End of information about pagers")
            emitSignal(AS_SIGNAL(InputHandler::addPagerSignal), data);
        else
            findByPath("/")->setState(2);
    }
    if (message == "COMMAND")
    {
        if (data != "Turn off the system")
        {
            if (prevSent != 0 && data.rfind("Send a message") != 0)
            {
                tick++;
                emitSignal(AS_SIGNAL(InputHandler::onTickSignal),
                           std::to_string(tick));
            }
            if (tryParseCMD(data, "SHOWTREE"))
                emitSignal(AS_SIGNAL(InputHandler::onShowTreeSignal),
                           "SHOWTREE");
            if (tryParseCMD(data, "Display the system status"))
                emitSignal(AS_SIGNAL(InputHandler::onGetSystemStatusSignal), data);
            if (tryParseCMD(data, "Display the pager status"))
            emitSignal(AS_SIGNAL(InputHandler::onGetPagerStatusSignal), data);
            if (tryParseCMD(data, "Send a message"))
            {
                emitSignal(AS_SIGNAL(InputHandler::onSendMessageSignal),
                           data);
                prevSent++;
            }
            else
            {
                tick++;
                emitSignal(AS_SIGNAL(InputHandler::onTickSignal),
                           std::to_string(tick));
                prevSent = 0;
            }
        }
        else
            findByPath("/")->setState(3);
    }
}
bool InputHandler::tryParseCMD(std::string& data, std::string cmd)
{
    if (data == cmd)
    {
        data = "";
        return true;
    }
    if (data.rfind(cmd) == 0)
    {
        data = data.substr(cmd.length() + 1);
        return true;
    }
    return false;
}
