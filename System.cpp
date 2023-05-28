//
// Created by Vlad04 on 28.05.2023.
//

#include "System.h"

System::System(TreeNode* head) : TreeNode(head) { }
void System::build()
{
    setName("SYSTEM");
    TreeNode* inputHandler = new InputHandler(this, "INPUT_HANDLER");
    TreeNode* outputHandler = new OutputHandler(this, "OUTPUT_HANDLER");
    TreeNode* operatorObject = new Operator(this, "OPERATOR");
    enableRecursively();
    link( //Require input
            AS_SIGNAL(System::requireInputSignal),
            inputHandler,
            AS_HANDLER(InputHandler::handleRequireInput)
    );
    link( //Show message
            AS_SIGNAL(System::printMessageSignal),
            outputHandler,
            AS_HANDLER(OutputHandler::handlePrintMessage)
    );
    operatorObject->link( //Show message from Operator
            AS_SIGNAL(Operator::sendErrorMessage),
            outputHandler,
            AS_HANDLER(OutputHandler::handlePrintMessage)
    );
    inputHandler->link( //Add pager (to this)
            AS_SIGNAL(InputHandler::addPagerSignal),
            this,
            AS_HANDLER(System::handlePagerAdd)
    );
    inputHandler->link( //Handle show tree
            AS_SIGNAL(InputHandler::onShowTreeSignal),
            outputHandler,
            AS_HANDLER(OutputHandler::handlePrintMessage)
    );
    inputHandler->link( //Handle get system status
            AS_SIGNAL(InputHandler::onGetSystemStatusSignal),
            this,
            AS_HANDLER(System::handleGetSystemStatus)
    );
    while (getState() != 2)
    {
        emitSignal(
                AS_SIGNAL(System::requireInputSignal),
                "PAGER"
        );
    }
    emitSignal(
            AS_SIGNAL(System::printMessageSignal),
            "Ready to work"
    );
}
int System::run()
{
    enableRecursively();
    while (getState() != 3)
    {
        emitSignal(
                AS_SIGNAL(System::requireInputSignal),
                "COMMAND"
        );
    }
    emitSignal(
            AS_SIGNAL(System::printMessageSignal),
            "Turn off the ATM"
    );
    return 0;
}
void System::requireInputSignal(std::string& message) { }
void System::printMessageSignal(std::string& message) { }
void System::handlePagerAdd(std::string message)
{
    TreeNode* operatorObject = findByPath("/OPERATOR");
    TreeNode* inputHandler = findByPath("/INPUT_HANDLER");
    TreeNode* outputHandler = findByPath("/OUTPUT_HANDLER");
    Pager* pager = new Pager(findByPath("/OPERATOR"), message);
    operatorObject->link(
            AS_SIGNAL(Operator::processSendMessageSignal),
            pager,
            AS_HANDLER(Pager::handleReceiveMessage)
    );
    pager->link(
            AS_SIGNAL(Pager::sendMessageSignal),
            operatorObject,
            AS_HANDLER(Operator::handleSendMessage)
    );
    pager->link(
            AS_SIGNAL(Pager::sendSentMessagesSignal),
            outputHandler,
            AS_HANDLER(OutputHandler::handlePrintMessage)
    );
    inputHandler->link(
            AS_SIGNAL(InputHandler::onTickSignal),
            operatorObject,
            AS_HANDLER(Operator::handleTick)
    );
    inputHandler->link(
            AS_SIGNAL(InputHandler::onTickSignal),
            pager,
            AS_HANDLER(Pager::handleTick)
    );
    inputHandler->link(
            AS_SIGNAL(InputHandler::onSendMessageSignal),
            pager,
            AS_HANDLER(Pager::handleSendMessage)
    );
    inputHandler->link(
            AS_SIGNAL(InputHandler::onGetPagerStatusSignal),
            pager,
            AS_HANDLER(Pager::handleGetSentMessages)
    );
}
void System::handleGetSystemStatus(std::string message)
{
    Operator* op = (Operator*)findByPath("/OPERATOR");
    std::string report = "";
    std::vector<Pager*> pagers;
    for (int i = 0; i < op->getInnerNodes().size(); i++)
        pagers.push_back((Pager*)op->getInnerNodes().at(i));
    while (pagers.size() != 0)
    {
        int minNum = 999999999;
        Pager* pager = nullptr;
        for (int j = 0; j < pagers.size(); j++)
        {
            int num = pagers[j]->getNumber();
            if (num < minNum)
            {
                pager = pagers[j];
                minNum = num;
            }
        }
        report += pager->getStatus() + "\n";
        pagers.erase(std::find(pagers.begin(), pagers.end(), pager));
    }
    report += op->getStatus();
    emitSignal(AS_SIGNAL(System::printMessageSignal), report);
}