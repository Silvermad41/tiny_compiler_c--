#include "../include/lexer.h"

Token_type &operator++(Token_type &token)
{
    if (token == Token_type::Gteq)
    {
        throw out_of_range("for Token_type& operator ++ (Token_type&)");
    }
    token = Token_type(static_cast<underlying_type<Token_type>::type>(token) + 1);
    return token;
}

static map<Token_type, string> TokenTypeStrings = {{Eof, "EOF"},
                                                   {Newline, "NEWLINE"},
                                                   {Number, "NUMBER"},
                                                   {Ident, " IDENT"},
                                                   {String, "STRING"},
                                                   {Label, "LABEL"},
                                                   {Goto, "GOTO"},
                                                   {Print, "PRINT"},
                                                   {Input, "INPUT"},
                                                   {Let, "LET"},
                                                   {If, "IF"},
                                                   {Then, "THEN"},
                                                   {Endif, "ENDIF"},
                                                   {While, "WHILE"},
                                                   {Repeat, "REPEAT"},
                                                   {Endwhile, "ENDWHILE"},
                                                   {Eq, "EQ"},
                                                   {Plus, "PLUS"},
                                                   {Minus, "MINUS"},
                                                   {Asterisk, "ASTERISK"},
                                                   {Slash, "SLASH"},
                                                   {Eqeq, "EQEQ"},
                                                   {noteq, "NOTEQ"},
                                                   {Lt, "LT"},
                                                   {Lteq, "LTEQ"},
                                                   {Gt, "GT"},
                                                   {Gteq, "GTEQ"}};

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
    this->skip_comment();

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
    else if (this->current_char == '\"')
    {
        this->next_char();
        int start_pos = this->current_pos;

        while (this->current_char != '\"')
        {
            if (this->current_char == '\r' || this->current_char == '\n' || this->current_char == '\\' || this->current_char == '%' || this->current_char == '\t')
            {
                this->abort("Character not allowed in String.");
            }
            this->next_char();
        }

        // possible + 1
        string token_text = this->source.substr(start_pos, this->current_pos - start_pos);
        token = Token(token_text, Token_type::String);
    }
    else if (isdigit(this->current_char))
    {
        int start_pos = this->current_pos;

        while (isdigit(this->peek()))
        {
            this->next_char();
        }

        if (this->peek() == '.')
        {
            this->next_char();

            if (!isdigit(this->peek()))
            {
                this->abort("Character not a Number");
            }

            while (isdigit(this->peek()))
            {
                this->next_char();
            }
        }

        string token_text = this->source.substr(start_pos, this->current_pos - start_pos);
        token = Token(token_text, Token_type::Number);
    }
    else if (isalpha(this->current_char))
    {
        int start_pos = this->current_pos;

        while (isalnum(this->peek()))
        {
            this->next_char();
        }

        string token_text = this->source.substr(start_pos, this->current_pos - start_pos + 1);

        Token_type keyword;
        bool is_keyword = check_if_keyword(token_text, &keyword);

        if (is_keyword)
        {
            token = Token(token_text, Token_type::Ident);
        }
        else
        {
            token = Token(token_text, keyword);
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

void Lexer::skip_comment()
{
    if (this->current_char == '#')
    {
        while (this->current_char != '\n')
        {
            this->next_char();
        }
    }
}
Token::Token(string text, Token_type kind)
{
    this->token_text = text;
    this->kind = kind;
}

bool check_if_keyword(string token_text, Token_type *token)
{
    for (Token_type kind = Token_type::Eof; kind != Token_type::Gteq; ++kind)
    {
        if (token_text.compare(TokenTypeToString(kind)) == 0 && kind >= 100 && kind <= 200)
        {
            *token = kind;
            return false;
        }
    }

    return true;
}