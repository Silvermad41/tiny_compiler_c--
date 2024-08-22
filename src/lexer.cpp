#include "../include/lexer.h"

Lexer::Lexer(string source)
{
    this->source = source;
    this->current_char = '\0';
    this->current_pos = -1;
    next_char();
}

char Lexer::peek()
{
    if (this->current_pos + 1 >= this->source.length())
    {
        return '\0';
    }
    else
    {
        return this->source[this->current_pos + 1];
    }
}

void Lexer::next_char()
{
    this->current_pos++;

    if (this->current_pos >= this->source.length())
    {
        this->current_pos = '\0';
    }
    else
    {
        this->current_char = this->source[this->current_pos];
    }
}