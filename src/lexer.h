#pragma once

#include <string>

class Lexer
{
    public:    
        int gettok();
        explicit Lexer(const std::string &source);
        virtual ~Lexer() = default;
        const std::string identifier() const;
        const double number() const;

        /*!
        * \brief The Lexer returns tokens [0-255] if it is an unknown character,
        * otherwise one of these for known things.
        */
        enum class Token
        {
            eof = -1,
            delimiter = -2,     // TODO: add this to gettok() ';'
            function = -3,
            returning = -4,
            identifier = -5,
            number = -6,
            equals = -7,
        };
        std::string functionIdentifier_;
        std::string commentsIdentifier_;
        std::string returningIdentifier_;
        std::string equalsIdentifier_;

    private:
        virtual int getchar();

        const std::string source_;
        int index;
        std::string identifierAsString_;
        double numberValue_;
};
