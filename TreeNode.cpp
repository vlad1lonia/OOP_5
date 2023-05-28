//
// Created by Vlad04 on 28.05.2023.
//

#include "TreeNode.h"

bool operator==(const Connection& con1, const Connection& con2)
{
    return con1.signal == con2.signal && con1.handlerNode == con2.handlerNode &&
           con1.handler == con2.handler;
}
TreeNode::TreeNode(TreeNode* head, std::string nodeName)
{
    this->head = head;
    this->name = nodeName;
    if (head != nullptr)
        this->head->innerNodes.push_back(this);
}
TreeNode::~TreeNode()
{
    for (int i = 0; i < this->innerNodes.size(); i++)
        delete this->innerNodes[i];
}
void TreeNode::setName(std::string objectName)
{
    this->name = objectName;
}
std::string TreeNode::getName()
{
    return this->name;
}
void TreeNode::setHead(TreeNode* newHead)
{
    if (this->head != nullptr && newHead != nullptr)
    {
        this->head->innerNodes.erase(std::find(this->head->innerNodes.begin(),
                                               this->head->innerNodes.end(), this));
        this->head = newHead;
        this->head->innerNodes.push_back(this);
    }
}
TreeNode* TreeNode::getHeadPtr()
{
    return this->head;
}
void TreeNode::printBranch(bool withState, int depth)
{
    if (depth != 0)
        std::cout << std::endl;
    for (int i = 0; i < depth; i++)
        std::cout << " ";
    std::cout << this->name;
    if (withState)
        std::cout << ((state != 0) ? " is ready" : " is not ready");
    for (int i = 0; i < innerNodes.size(); i++)
        innerNodes[i]->printBranch(withState, depth + 1);
}
TreeNode* TreeNode::findByName(std::string name, bool fromRoot)
{
    TreeNode* fNode = this;
    if (fromRoot)
    {
        while (fNode->head != nullptr)
            fNode = fNode->head;
    }
    if (this->name == name)
        return this;
    for (int i = 0; i < fNode->innerNodes.size(); i++)
    {
        TreeNode* temp = fNode->innerNodes[i]->findByName(name, false);
        if (temp != nullptr)
            return temp;
    }
    return nullptr;
}
void TreeNode::setState(int state)
{
    if (state == 0)
    {
        this->state = state;
        for (int i = 0; i < innerNodes.size(); i++)
            innerNodes[i]->setState(state);
    }
    else
    {
        if (this->head == nullptr || (this->head != nullptr && this->head->state != 0))
        this->state = state;
    }
}
void TreeNode::enableRecursively()
{
    setState(1);
    if (this->state != 0)
    {
        for (int i = 0; i < innerNodes.size(); i++)
            innerNodes[i]->enableRecursively();
    }
}
TreeNode* TreeNode::findByPath(std::string path)
{
    if (path.rfind("//", 0) == 0)
        return findByName(path.substr(2));
    TreeNode* fNode = this;
    if (path[0] == '/')
    {
        while (fNode->head != nullptr)
            fNode = fNode->head;
        path = path.substr(1);
    }
    std::stringstream stream(path);
    std::string nodeName;
    while (std::getline(stream, nodeName, '/') && nodeName != "")
    {
        if (nodeName == ".")
            continue;
        TreeNode* nNode = nullptr;
        for (int i = 0; i < fNode->innerNodes.size(); i++)
        {
            if (fNode->innerNodes[i]->getName() == nodeName)
            {
                nNode = fNode->innerNodes[i];
                break;
            }
        }
        fNode = nNode;
        if (fNode == nullptr)
            break;
    }
    return fNode;
}
std::string TreeNode::getPath(bool endSlash)
{
    if (this->head != nullptr)
        return this->head->getPath(true) + this->name + (endSlash ? "/" : "");
    else
        return "/";
}
int TreeNode::getState()
{
    return this->state;
}
void TreeNode::link(signalPtr signal, TreeNode* handlerNode, handlerPtr handler)
{
    for (int i = 0; i < connections.size(); i++)
    {
        Connection con = connections[i];
        if (con.signal == signal && con.handlerNode == handlerNode &&
            con.handler == handler)
            return;
    }
    Connection con;
    con.signal = signal;
    con.handlerNode = handlerNode;
    con.handler = handler;
    connections.push_back(con);
}
void TreeNode::unlink(signalPtr signal, TreeNode* handlerNode, handlerPtr handler)
{
    for (int i = 0; i < connections.size(); i++)
    {
        Connection con = connections[i];
        if (con.signal == signal && con.handlerNode == handlerNode &&
            con.handler == handler)
        {
            connections.erase(std::find(connections.begin(),
                                        connections.end(), con));
            break;
        }
    }
}
void TreeNode::emitSignal(signalPtr signal, std::string message)
{
    if (getState() == 0)
        return;
    (this->*signal)(message);
    for (int i = 0; i < connections.size(); i++)
    {
        Connection con = connections[i];
        if (con.signal == signal && con.handlerNode->getState() != 0)
            ((con.handlerNode)->*(con.handler))(message);
    }
}
std::vector<TreeNode*> TreeNode::getInnerNodes()
{
    return innerNodes;
}