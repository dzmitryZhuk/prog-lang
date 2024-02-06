#pragma once

#include "lexer.h"

#include <map>
#include <string>
#include <filesystem>

class Parser
{
    public:
        Parser(const std::filesystem::path &path);
        virtual ~Parser() = default;
        std::vector<Lexer::Token> tokenize(const std::string & source);
        // /// GetTokPrecedence - Get the precedence of the pending binary operator token.
        // static int GetTokPrecedence() {
        // if (!isascii(currentToken_))
        //     return -1;

        // // Make sure it's a declared binop.
        // int TokPrec = m_binopPrecedence[currentToken_];
        // if (TokPrec <= 0)
        //     return -1;
        // return TokPrec;
        // }
    private:
        std::unique_ptr<Lexer> lexer_;
        std::filesystem::path file_;
        //int getNextToken() { return currentToken_ = gettok(); }
        int currentToken_;
        // // BinopPrecedence - This holds the precedence for each binary operator that is defined
        // static std::map<char, int> m_binopPrecedence;
};
