#pragma once

#include "lexer.h"
#include "ast.h"

#include <map>
#include <string>
#include <filesystem>
#include <memory>

class Parser
{
    public:
        Parser(const std::filesystem::path &path);
        virtual ~Parser() = default;
        std::unique_ptr<ASTNode> parse();

    protected:
        std::unique_ptr<ASTNode> parse(const std::vector<Lexer::TokenTuple>& tokens);

    private:
        std::unique_ptr<Lexer> lexer_;
        std::filesystem::path file_;
};
