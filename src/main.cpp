#include "../include/lexer.h"
#include <iostream>

int main(){
    std::string code = "while x = 42";
    Lexer lexer(code);

    std::vector<Token> tokens = lexer.scanTokens();
    lexer.printTokens(tokens);
    std::cout << "Tokens scanned: " << tokens.size() << std::endl;
    return 0;

}