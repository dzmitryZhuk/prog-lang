#pragma once

#include <string>

class Lexer
{
    public:    
        int gettok();
        Lexer();
        virtual ~Lexer() = default;

        /*!
        * \brief The Lexer returns tokens [0-255] if it is an unknown character,
        * otherwise one of these for known things.
        */
        enum class Token
        {
            eof = -1,
            delimiter = -2,     // TODO: add this to gettok()
            function = -3,
            identifier = -4,
            number = -5,
        };
        std::string identifierAsString_;
        double numberValue_;
        std::string functionIdentifier_;
        std::string commentsIdentifier_;

    private:
        virtual int getchar();
};
