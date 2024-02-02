#pragma once

#include <string>

class Lexer
{
public:
    std::string IdentifierStr; // Filled in if tok_identifier
    double NumVal;             // Filled in if tok_number

    // The Lexer returns tokens [0-255] if it is an unknown character, otherwise one
    // of these for known things.
    enum class Token {
        tok_eof = -1,
        tok_delimiter = -2,     // TODO: add to gettok()

        // commands
        tok_function = -3,
        //tok_extern = -4,

        // primary
        tok_identifier = -5,
        tok_number = -6,
    };
// ==================================================================================
    int gettok();
    Lexer();
    virtual ~Lexer() = default;

private:
    virtual int f_getchar();
};
