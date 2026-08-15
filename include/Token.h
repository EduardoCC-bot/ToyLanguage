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

