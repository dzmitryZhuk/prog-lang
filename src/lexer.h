#ifndef _COMPILLER_LEXER_H_
#define _COMPILLER_LEXER_H_

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

        // commands
        tok_function = -2,
        //tok_extern = -3,

        // primary
        tok_identifier = -4,
        tok_number = -5,
    };
// ==================================================================================
    int gettok();
    Lexer();
    virtual ~Lexer() = default;

private:
    virtual int f_getchar();
};

#endif