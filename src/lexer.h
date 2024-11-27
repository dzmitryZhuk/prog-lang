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
    inline const std::string functionIdentifier() const { return functionIdentifier_; }
    inline const std::string commentsIdentifier() const { return commentsIdentifier_; }
    inline const std::string returningIdentifier() const { return returningIdentifier_; }
    inline const std::string assignmentIdentifier() const { return assignmentIdentifier_; }
    inline const std::string delimitertIdentifier() const { return delimitertIdentifier_; }

private:
    const std::string identifier() const;
    const double number() const;

    int gettok();
    virtual int getchar();

    const std::string source_;
    size_t index;
    size_t cur_line;        // number of current line in stream
    size_t cur_line_pos;    // number of current position in line
    std::string identifierAsString_;
    double numberValue_;

    std::string functionIdentifier_;
    std::string commentsIdentifier_;
    std::string returningIdentifier_;
    std::string assignmentIdentifier_;
    std::string delimitertIdentifier_;
};
