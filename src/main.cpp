#include "../include/Lexer.h"
#include "../include/parser.h"
#include <iostream>

int main(){
    std::string code = "x = 42;";
    Lexer lexer(code);

    std::vector<Token> tokens = lexer.scanTokens();
    lexer.printTokens(tokens);

    Parser parser(tokens);
    std::unique_ptr<ASTNode> ast = parser.parse();

    if (ast != nullptr){
        std::cout << "Funciona !! " << std::endl;
    }else {
        std::cout << "Error" << std::endl;
    }
    return 0;
}