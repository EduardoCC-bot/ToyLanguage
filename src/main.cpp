#include "../include/Lexer.h"
#include "../include/parser.h"
#include <iostream>

int main(){
    //std::string code = "x = 42; y = x + 5;";
    std::string code = 
    "x = 10; "
    "{ "
    "   y = 50; "
    "} "
    "x = y + 1;";

    Lexer lexer(code);

    std::vector<Token> tokens = lexer.scanTokens();
    //lexer.printTokens(tokens);

    Parser parser(tokens);
    std::unique_ptr<ASTNode> ast = parser.parse();

    
    if (ast != nullptr){
        std::cout << " ESTRUCTURA DEL AST " << std::endl;
        ast->print();
        

        Environment globalEnv;
        try {
            ast->eval(globalEnv);
        } catch (const std::runtime_error& e) {
            std::cerr << "Error en tiempo de ejecucion: " << e.what() << std::endl;
        }

        std::cout << "\n--- ESTADO DE LA MEMORIA (GLOBAL) ---\n";
        for (const auto& [var, val] : globalEnv.getValues()) {
            std::cout << var << " = " << val << "\n";
        }
        
        
    }else {
        std::cout << "Error en parsing" << std::endl;
    }
    return 0;
}