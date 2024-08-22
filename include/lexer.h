#ifndef __COLONY_H__
#define __COLONY_H__

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class Lexer
{
public:
    string source;

    Lexer(string);
    char peek();
    void next_char();
    char *get_token();

private:
    char current_char;
    long unsigned int current_pos;

    void abort();
    void skip_whitespace();
    void skip_comment();
};

#endif