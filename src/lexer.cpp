#include "lexer.h"

#include <type_traits>
#include <iostream>

Lexer::Lexer()
    : functionIdentifier_("function")
    , commentsIdentifier_("#")
{
}

int Lexer::gettok()
{
    static int lastChar = ' ';

    // Skip any whitespace.
    while(isspace(lastChar))
    {
        lastChar = std::move(getchar());
    }

    if(isalpha(lastChar))  // [a-zA-Z]
    {
        do
        {
            identifierAsString_ += lastChar;
            lastChar = std::move(getchar());
        } while(isalnum(lastChar));    // [a-zA-Z0-9]

        if(identifierAsString_ == functionIdentifier_)
        {
            return static_cast<int>(Token::function);
        }

        if(identifierAsString_ == commentsIdentifier_)
        {
            // Comment until end of line.
            do
                lastChar = std::move(getchar());
            while(lastChar != EOF && lastChar != '\n' && lastChar != '\r');

            if (lastChar != EOF)
                return gettok();
        }
        
        return static_cast<int>(Token::identifier);
    }

    if(isdigit(lastChar) || lastChar == '.')    // [0-9.]+
    {
        std::string numStr;
        do
        {
            numStr += lastChar;
            lastChar = std::move(getchar());
        } while(isdigit(lastChar) || lastChar == '.');

        numberValue_ = strtod(numStr.c_str(), nullptr);
        return static_cast<int>(Token::number);
    }

    // Check for end of file.  Don't eat the EOF.
    if(lastChar == EOF)
    {
        return static_cast<int>(Token::eof);
    }

    int unknownToken = lastChar;
    lastChar = std::move(getchar());
    return unknownToken;
}

int Lexer::getchar()
{
    return std::cin.get();
}
