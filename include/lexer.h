#include "Token.h"
#include <string>
#include <vector>

class Lexer {
public:
    Lexer(const std::string& source); 
    std::vector<Token> scanTokens();
    void addToken(std::vector<Token>& tokens, TokenType type, const std::string& value);

private:
    std::string source;
    size_t start = 0;
    size_t current = 0;
    int line = 1;


    bool isAtEnd() const;
    char advance();
    bool isDigit(char c) const;
    bool isAlpha(char c) const;
    char peek() const { return isAtEnd() ? '\0' : source[current]; }

};