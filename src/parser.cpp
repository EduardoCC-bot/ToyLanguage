#include "../include/Parser.h"
#include "../include/AST.h"
#include "../include/Token.h"
#include <iostream>
#include <stdexcept>

Parser:: Parser(const std::vector<Token>& tokens) : tokens(tokens) {}

Token Parser::peek() const {
    return tokens[current];
}

Token Parser::previous() const{
    return tokens[current - 1];
}

bool Parser::isAtEnd() const {
    return peek().type == TokenType::EOF_TOKEN;
}

Token Parser:: advance(){
    if (!isAtEnd()) current++;
    return previous();
}


bool Parser::check(TokenType type) const {
    if (isAtEnd()) return false;
    return peek().type == type;
}

bool Parser::match(TokenType type) {
    if (check(type)) {
        advance();
        return true;
    }
    return false;
}


Token Parser::consume(TokenType type, const std::string& message){
    if (check(type)) return advance();
    throw std::runtime_error("Error sintactico en linea: " + message);
}

std::unique_ptr<ASTNode> Parser::expression(){

    if (match(TokenType::INT_LITERAL)){
        int val = std::stoi(previous().value);
        return std::make_unique<LiteralNode>(val);
    }

    if (match(TokenType::IDENTIFIER)){
        return std::make_unique<VariableNode>(previous().value);
    }
    throw std::runtime_error("Se esperaba una expresion en linea: " + std::to_string(peek().line));
}

std::unique_ptr<ASTNode> Parser::statement(){

    if (check(TokenType::IDENTIFIER)){
        Token nameToken = advance();

        if (match(TokenType::ASSIGN)){
            auto expr = expression();
            consume(TokenType::SEMICOLON, "Se esperaba un ';' al final de la asignacion");
            return std::make_unique<AssignmentNode>(nameToken.value, std::move(expr));
        }

        current--;

    }
    throw std::runtime_error("Instruccion no reconocida en linea: " + std::to_string(peek().line));

}

std::unique_ptr<ASTNode> Parser::parse(){
    try{
        return statement();
    } catch (const std::exception& e){
        std::cerr << e.what() << std::endl;
        return nullptr;
    }
}