#pragma once

#include <string>
#include <memory>

class ASTNode {
public:
    virtual ~ASTNode() = default;
};


class LiteralNode : public ASTNode{
public:
    int value;
    LiteralNode(int val) : value(val){}
};


class VariableNode : public ASTNode{
public:
    std::string name;
    VariableNode(const std::string& varName) : name(varName){}
};


class AssignmentNode : public ASTNode{
public:
    std::string name;
    std::unique_ptr<ASTNode> value;

    AssignmentNode(const std::string& varName, std::unique_ptr<ASTNode> val)
        : name(name), value(std::move(val)){}
};
