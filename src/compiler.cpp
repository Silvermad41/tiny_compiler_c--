#include <stdio.h>
#include <iostream>
#include "../include/lexer.h"

int main(int argc, char *argv[])
{
    Lexer new_lexer("+- */");

    Token token = new_lexer.get_token();

    token = new_lexer.get_token();

    if (token.kind == Minus)
    {
        std::cout << token.kind;
    }

    return 0;
}