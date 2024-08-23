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

Token Lexer::get_token()
{
    string current_char_to_string(1, this->current_char);
    string next_char_to_string(1, this->peek());
    Token token;

    if (this->current_char == '+')
    {
        token = Token(current_char_to_string, Plus);
    }
    else if (this->current_char == '-')
    {
        token = Token(current_char_to_string, Minus);
    }
    else if (this->current_char == '*')
    {
        token = Token(current_char_to_string, Asterisk);
    }
    else if (this->current_char == '/')
    {
        token = Token(current_char_to_string, Slash);
    }
    else if (this->current_char == '\n')
    {
        token = Token(current_char_to_string, Newline);
    }
    else if (this->current_char == '\0')
    {
        token = Token(current_char_to_string, Eof);
    }
    else
    {
    }

    this->next_char();
    return token;
}

Token::Token(string text, Token_type kind)
{
    this->token_text = text;
    this->kind = kind;
}