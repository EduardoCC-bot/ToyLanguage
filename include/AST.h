#pragma once

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include "Environment.h"

class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual void print(int indent = 0) const = 0;
    virtual int eval(Environment& env) = 0;
};


class LiteralNode : public ASTNode{
public:
    int value;
    LiteralNode(int val) : value(val){}

    void print(int indent = 0) const override {
        std::string padding(indent * 4, ' ');
        std::cout << padding << "LiteralNode: (" << value << ")\n";
    }

    int eval(Environment&) override {
        return value;
    }
};


class VariableNode : public ASTNode{
public:
    std::string name;
    VariableNode(const std::string& varName) : name(varName){}

        void print(int indent = 0) const override {
        std::string padding(indent * 4, ' ');
        std::cout << padding << "VariableNode: (" << name << ")\n";
    }

    int eval(Environment& env) override {
        return env.get(name);
    }
};


class AssignmentNode : public ASTNode{
public:
    std::string name;
    std::unique_ptr<ASTNode> value;

    AssignmentNode(const std::string& varName, std::unique_ptr<ASTNode> val)
        : name(varName), value(std::move(val)){}

    void print(int indent = 0) const override {
        std::string padding(indent * 4, ' ');
        std::cout << padding << "AssignmentNode: (" << name << ")\n";
        if (value) {
            value->print(indent + 1);
        }
    }

    int eval(Environment& env ) override {
        int val = value->eval(env);
        env.set(name, val);
        return val;
    }
};

class ProgramNode : public ASTNode {
public:
    std::vector<std::unique_ptr<ASTNode>> statements;

    void addStatement(std::unique_ptr<ASTNode> stmt) {
        statements.push_back(std::move(stmt));
    }

    void print(int indent = 0) const override {
        std::string padding(indent * 4, ' ');
        std::cout << padding << "ProgramNode\n";
        for (const auto& stmt : statements) {
            stmt->print(indent + 1);
        }
    }

    int eval(Environment& env) override {  
        int lastVal = 0;
        for (const auto& stmt : statements) {
            lastVal = stmt->eval(env);
        }
        return lastVal;
    }
};

class BinaryOpNode : public ASTNode {
public:
    std::string op;
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;

    BinaryOpNode(const std::string& op, std::unique_ptr<ASTNode> left, std::unique_ptr<ASTNode> right)
        : op(op), left(std::move(left)), right(std::move(right)) {}

        void print(int indent = 0) const override {
            std::string padding(indent * 4, ' ');
            std::cout << padding << "BinaryOpNode: (" << op << ")\n";
            if (left) left->print(indent + 1);
            if (right) right->print(indent + 1);
        }

    int eval(Environment& env) override {
        int leftVal = left->eval(env);
        int rightVal = right->eval(env);

        if (op == "+") return leftVal + rightVal;
        if (op == "-") return leftVal - rightVal;

        throw std::runtime_error("Operador desconocido: " + op);
    }
};


class BlockNode : public ASTNode {
public :
    std::vector<std::unique_ptr<ASTNode>> statements;
    
    void addstatement(std::unique_ptr<ASTNode> stmt) {
        statements.push_back(std::move(stmt));
    }

    void print(int indent = 0) const override {
        std::string padding(indent * 4, ' ');
        std::cout << padding << "BlockNode {\n";
        for (const auto& stmt : statements) {
            stmt->print(indent + 1);
        }
        std::cout << padding << "}\n";
    }


    int eval(Environment& env) override {
        Environment blockEnv(&env);

        int lastVal = 0;
        for (const auto& stmt : statements) {
            lastVal = stmt->eval(blockEnv);
        }
        return lastVal;
    }
};
