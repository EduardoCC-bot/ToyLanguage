#include "../include/Lexer.h"
#include <iostream>

Lexer::Lexer(const std::string& source) : source(source){}

bool Lexer::isAtEnd() const{
    return current >= source.length();
}

char Lexer::advance(){
    return source[current++];
}

bool Lexer::isDigit(char c) const{
    return c >= '0' && c <= '9';
}

bool Lexer::isAlpha(char c) const{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

void Lexer::printTokens(const std::vector<Token>& tokens) const {
    for (const auto& token : tokens) {
        std::cout << "Token: " << tokenTypeToString(token.type) 
                  << " | Value: '" << token.value << "'" 
                  << " | Line: " << token.line << "\n";
    }
}

void Lexer::addToken(std::vector<Token>& tokens, TokenType type, const std::string& value){
    tokens.push_back({type, value, line});
}

std::vector<Token> Lexer::scanTokens(){
    std::vector<Token> tokens; 
    while (!isAtEnd()){
        start = current;
        char c = advance();
        
        switch (c){
            case '+': addToken(tokens, TokenType::PLUS, "+"); break;
            case '-': addToken(tokens, TokenType::MINUS, "-"); break;
            case ';': addToken(tokens, TokenType::SEMICOLON, ";"); break;
            case '=': addToken(tokens, TokenType::ASSIGN, "="); break;
            
            case ' ': 
            case '\r':
            case '\t':
            break;
            case '\n':
            line++;
            break;
            
            default:
            if(isDigit(c)){
                while (isDigit(peek())) advance();
                std::string value = source.substr(start, current - start);
                addToken(tokens, TokenType::INT_LITERAL, value);
            }
            
            else if(isAlpha(c)){
                while (isAlpha(peek()) || isDigit(peek())) advance();
                std::string text = source.substr(start, current - start);
                
                if(text == "while") addToken(tokens, TokenType::WHILE_LOOP, text);
                else if(text ==  "for") addToken(tokens, TokenType::FOR_LOOP, text);
                else addToken(tokens, TokenType::IDENTIFIER, text);
            }
            
            else{
                std::cerr << "Unexpected character: " << c << " at line " << line << std::endl;
            }
        }

    }
    addToken(tokens, TokenType::EOF_TOKEN, "");
    return tokens;
}