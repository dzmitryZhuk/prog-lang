#pragma once

#include <map>
#include <string>

class Parser
{
    int m_curTok;
    // BinopPrecedence - This holds the precedence for each binary operator that is defined
    static std::map<char, int> m_binopPrecedence;
public:
    //int getNextToken() { return m_curTok = gettok(); }

    /// GetTokPrecedence - Get the precedence of the pending binary operator token.
    static int GetTokPrecedence() {
    if (!isascii(m_curTok))
        return -1;

    // Make sure it's a declared binop.
    int TokPrec = m_binopPrecedence[m_curTok];
    if (TokPrec <= 0)
        return -1;
    return TokPrec;
    }
};
