#include "../include/lexer.h"

// skip comment next function

string TokenTypeToString(Token_type token)
{
    return TokenTypeStrings[token];
}

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
    this->current_pos += 1;

    if (this->current_pos > this->source.length())
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

    this->skip_whitespace();

    if (this->current_char == '+')
    {
        token = Token(current_char_to_string, Token_type::Plus);
    }
    else if (this->current_char == '-')
    {
        token = Token(current_char_to_string, Token_type::Minus);
    }
    else if (this->current_char == '*')
    {
        token = Token(current_char_to_string, Token_type::Asterisk);
    }
    else if (this->current_char == '/')
    {
        token = Token(current_char_to_string, Token_type::Slash);
    }
    else if (this->current_char == '\n')
    {
        token = Token(current_char_to_string, Token_type::Newline);
    }
    else if (this->current_char == '\0')
    {
        token = Token("\0", Token_type::Eof);
    }
    else if (this->current_char == '=')
    {
        if (this->peek() == '=')
        {
            string EQEQ_text = current_char_to_string;
            EQEQ_text += this->peek();
            this->next_char();
            token = Token(EQEQ_text, Token_type::Eqeq);
        }
        else
        {
            token = Token(current_char_to_string, Token_type::Eq);
        }
    }
    else if (this->current_char == '>')
    {
        if (this->peek() == '=')
        {
            string GTEQ_text = current_char_to_string;
            GTEQ_text += this->peek();
            this->next_char();
            token = Token(GTEQ_text, Token_type::Gteq);
        }
        else
        {
            token = Token(current_char_to_string, Token_type::Gt);
        }
    }
    else if (this->current_char == '<')
    {
        if (this->peek() == '=')
        {
            string LTEG_text = current_char_to_string;
            LTEG_text += this->peek();
            this->next_char();
            token = Token(LTEG_text, Token_type::Lteq);
        }
        else
        {
            token = Token(current_char_to_string, Token_type::Lt);
        }
    }
    else if (this->current_char == '!')
    {
        if (this->peek() == '=')
        {
            string NOTEQ_text = current_char_to_string;
            NOTEQ_text += this->peek();
            this->next_char();
            token = Token(NOTEQ_text, Token_type::noteq);
        }
        else
        {
            this->abort("Expected !=, got !" + this->peek());
        }
    }
    else
    {
        string error_message = "Unknown token : ";
        error_message += this->current_char;
        this->abort(error_message);
    }

    this->next_char();
    return token;
}

void Lexer::abort(string message)
{
    cout << "Lexing error. " << message << "\n";
    exit(0);
}

void Lexer::skip_whitespace()
{
    while (this->current_char == ' ' or this->current_char == '\t' or this->current_char == '\r')
    {
        this->next_char();
    }
}

Token::Token(string text, Token_type kind)
{
    this->token_text = text;
    this->kind = kind;
}