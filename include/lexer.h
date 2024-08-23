#ifndef __COLONY_H__
#define __COLONY_H__

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

enum Token_type
{
    Eof = -1,
    Newline = 0,
    Number = 1,
    Ident = 2,
    String = 3,
    Label = 101,
    Goto = 102,
    Print = 103,
    Input = 104,
    Let = 105,
    If = 106,
    Then = 107,
    Endif = 108,
    While = 109,
    Repeat = 110,
    Endwhile = 111,
    Eq = 201,
    Plus = 202,
    Minus = 203,
    Asterisk = 204,
    Slash = 205,
    Eqeq = 206,
    noteq = 207,
    Lt = 208,
    Lteq = 209,
    Gt = 210,
    Gteq = 211,
};

class Token
{
public:
    string token_text;
    Token_type kind;
    Token() = default;
    Token(string, Token_type);
};

class Lexer
{
public:
    string source;

    Lexer(string);
    char peek();
    void next_char();
    Token get_token();

private:
    char current_char;
    long unsigned int current_pos;
    void abort();
    void skip_whitespace();
    void skip_comment();
};

#endif