#pragma once

#include <string>
#include <vector>
#include <variant>
#include <tuple>

class Lexer
{
public:
    /*!
    * \brief The Lexer returns tokens [0-255] if it is an unknown character,
    * otherwise one of these for known things.
    */
    enum class Token : int16_t
    {
        eof = -1,
        delimiter = -2,
        function = -3,
        returning = -4,
        identifier = -5,
        number = -6,
        assignment = -7,
    };

    using TokenValue = std::variant<std::monostate, std::string, double>;
    using TokenTuple = std::pair<Token, TokenValue>;

    std::vector<TokenTuple> tokenize();
    explicit Lexer(const std::string &source);
    virtual ~Lexer() = default;

private:
    const std::string identifier() const;
    const double number() const;

    int gettok();
    virtual int getchar();

    const std::string source_;
    int index;
    std::string identifierAsString_;
    double numberValue_;

    std::string functionIdentifier_;
    std::string commentsIdentifier_;
    std::string returningIdentifier_;
    std::string assignmentIdentifier_;
    std::string delimitertIdentifier_;
};
