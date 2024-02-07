#include "lexer.h"

#include <type_traits>
#include <iostream>

Lexer::Lexer(const std::string &source)
    : source_(source)
    , index(0)
    , functionIdentifier_("func")
    , commentsIdentifier_("#")
    , returningIdentifier_("ret")
    , assignmentIdentifier_("=")
{
}

const std::string Lexer::identifier() const
{
  return identifierAsString_;
}

const double Lexer::number() const
{
  return numberValue_;
}

int Lexer::gettok()
{
    static int lastChar = ' ';

    // Skip any whitespace.
    while (isspace(lastChar))
    {
        lastChar = std::move(getchar());
    }

    if (isalpha(lastChar))  // [a-zA-Z]
    {
        do
        {
            identifierAsString_ += lastChar;
            lastChar = std::move(getchar());
        } while (isalnum(lastChar));    // [a-zA-Z0-9]

        if (identifierAsString_ == functionIdentifier_)
        {
            identifierAsString_.clear();
            return static_cast<int>(Token::function);
        }

        if (identifierAsString_ == returningIdentifier_)
        {
            identifierAsString_.clear();
            return static_cast<int>(Token::returning);
        }
        
        return static_cast<int>(Token::identifier);
    }

    if (isdigit(lastChar) || lastChar == '.')    // [0-9.]+
    {
        std::string numStr;
        do
        {
            numStr += lastChar;
            lastChar = std::move(getchar());
        } while (isdigit(lastChar) || lastChar == '.');

        numberValue_ = strtod(numStr.c_str(), nullptr);
        return static_cast<int>(Token::number);
    }

    if (ispunct(lastChar))   // !"#$%&'()*+,-./:;<=>?@[\]^_`{|}~
    {
        identifierAsString_ = lastChar;

        if (identifierAsString_ == commentsIdentifier_)
        {
            identifierAsString_.clear();
            // Comment until end of line.
            do
            {
                    lastChar = std::move(getchar());
            }
            while (lastChar != EOF && lastChar != '\n' && lastChar != '\r');

            if (lastChar != EOF)
            {
                return gettok();
            }
        }

        if (identifierAsString_ == assignmentIdentifier_)
        {
            identifierAsString_.clear();
            return static_cast<int>(Token::assignment);
        }
    }

    if (lastChar == EOF)
    {
        return static_cast<int>(Token::eof);
    }

    int unknownToken = lastChar;
    lastChar = std::move(getchar());
    return unknownToken;
}

int Lexer::getchar()
{
    if (index == source_.size())
    {
        return EOF;
    }
    return source_.at(index++);
}
