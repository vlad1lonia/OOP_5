//
// Created by Vlad04 on 28.05.2023.
//

#ifndef OOP_5_COPIED_TREENODE_H
#define OOP_5_COPIED_TREENODE_H


#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
class TreeNode;
typedef void (TreeNode::* signalPtr)(std::string& message);
typedef void (TreeNode::* handlerPtr)(std::string message);
#define AS_SIGNAL(signalMethod) ((signalPtr)(&signalMethod))
#define AS_HANDLER(handlerMethod) ((handlerPtr)(&handlerMethod))
struct Connection
{
    signalPtr signal;
    TreeNode* handlerNode;
    handlerPtr handler;
};
class TreeNode
{
private:
    std::string name;
    int state = 0;
    TreeNode* head;
    std::vector<TreeNode*> innerNodes;
    std::vector<Connection> connections;
public:
    TreeNode(TreeNode* head, std::string nodeName = "default");
    ~TreeNode();
    void setName(std::string objectName);
    std::string getName();
    void setHead(TreeNode* newHead);
    TreeNode* getHeadPtr();
    void printBranch(bool withState, int depth = 0);
    TreeNode* findByName(std::string name, bool fromRoot = true);
    void setState(int state);
    int getState();
    TreeNode* findByPath(std::string path);
    std::string getPath(bool endSlash = false);
    void link(signalPtr signal, TreeNode* handlerNode, handlerPtr handler);
    void unlink(signalPtr signal, TreeNode* handlerNode, handlerPtr handler);
    void emitSignal(signalPtr signal, std::string message);
    void enableRecursively();
    std::vector<TreeNode*> getInnerNodes();
};



#endif //OOP_5_COPIED_TREENODE_H
