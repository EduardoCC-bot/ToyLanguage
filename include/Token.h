#pragma once

#include <string>

enum class  TokenType {
    INT_LITERAL,
    IDENTIFIER,
    ASSIGN,
    PLUS,
    MINUS,
    SEMICOLON, 
    EOF_TOKEN,
    WHILE_LOOP,
    FOR_LOOP,
};


struct Token {
    TokenType type;
    std::string value;
    int line;
};


inline std::string tokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::INT_LITERAL: return "INT_LITERAL";
        case TokenType::IDENTIFIER:  return "IDENTIFIER";
        case TokenType::ASSIGN:      return "ASSIGN";
        case TokenType::PLUS:        return "PLUS";
        case TokenType::MINUS:       return "MINUS";
        case TokenType::SEMICOLON:   return "SEMICOLON";
        case TokenType::EOF_TOKEN:   return "EOF_TOKEN";
        case TokenType::WHILE_LOOP:  return "WHILE_LOOP";
        case TokenType::FOR_LOOP:    return "FOR_LOOP";
        default:                     return "UNKNOWN";
    }
}