#include <type_traits>
#include <iostream>

#include "lexer.h"

int Lexer::gettok()
{
    static int LastChar = ' ';

    // Skip any whitespace.
    while (isspace(LastChar))
        LastChar = std::move(f_getchar());

    if (isalpha(LastChar)) { // identifier: [a-zA-Z][a-zA-Z0-9]*
        IdentifierStr = LastChar;
        while (isalnum((LastChar = std::move(f_getchar()))))
            IdentifierStr += LastChar;

        if (IdentifierStr == "function")
            return static_cast<int>(Token::tok_function);
        // if (IdentifierStr == "extern")
        // return static_cast<int>(Token::tok_extern);
        return static_cast<int>(Token::tok_identifier);
    }

    if (isdigit(LastChar) || LastChar == '.') { // Number: [0-9.]+
        std::string NumStr;
        do {
            NumStr += LastChar;
            LastChar = std::move(f_getchar());
        } while (isdigit(LastChar) || LastChar == '.');

        NumVal = strtod(NumStr.c_str(), nullptr);
        return static_cast<int>(Token::tok_number);
    }

    if (LastChar == '/') {
        // Comment until end of line.
        do
            LastChar = std::move(f_getchar());
        while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');

        if (LastChar != EOF)
            return gettok();
    }

    // Check for end of file.  Don't eat the EOF.
    if (LastChar == EOF)
        return static_cast<int>(Token::tok_eof);

    // Otherwise, just return the character as its ascii value.
    int ThisChar = LastChar;
    LastChar = std::move(f_getchar());
    return ThisChar;
}

int Lexer::f_getchar()
{
    return std::cin.get();
}
