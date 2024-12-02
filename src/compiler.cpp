#include <stdio.h>
#include <iostream>
#include "../include/lexer.h"

int main(int argc, char *argv[])
{
    Lexer new_lexer("+- */ >>= = !=");

    Token token = new_lexer.get_token();

    while (token.kind != Token_type::Eof)
    {
        std::cout << TokenTypeToString(token.kind) << ",\n ";
        token = new_lexer.get_token();
    }

    return 0;
}