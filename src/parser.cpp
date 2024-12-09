#include "parser.h"

#include <fstream>
#include <iostream>

Parser::Parser(const std::filesystem::path &path)
    : file_(path)
{
  std::ifstream stream{path};
  std::string fileContent((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
  stream.close();
  lexer_ = std::make_unique<Lexer>(fileContent);
}

std::unique_ptr<ASTNode> Parser::parse()
{
  auto tokens = lexer_.get()->tokenize();
  return parse(tokens);
}

std::unique_ptr<ASTNode> Parser::parse(const std::vector<Lexer::TokenTuple>& tokens)
{
  size_t currentIter = 0; // pointer for current token (iterator)
  std::unique_ptr<ASTNode> root = std::make_unique<ASTNode>();
  // start parsing

  while (currentIter < tokens.size()) {
    auto &[token, pos, value] = tokens[currentIter];

    switch (token) {
    case Lexer::Token::returning: {
        // parse "ret <smth>;"

        // skip "ret", it will be added at the end of expression
        currentIter++;
        if (currentIter >= tokens.size()) {
            auto error_message = std::format("line {}:{}:Expected some value after 'ret'", pos.first, pos.second); 
            std::cout << error_message;
            // throw std::runtime_error(error_message);
            break;
        }
        auto &[token1, pos1, value1] = tokens[currentIter];
        std::unique_ptr<ASTExpression> returnValue;

        // next token is number or variable
        if (token1 == Lexer::Token::number) {
            double number = std::get<double>(value1);
            returnValue = std::make_unique<ASTExpressionNumber>(number);
        } else {  // TODO: add case if some identifier or function call here
            auto error_message = std::format("line {}:{}:Expected a number after 'ret'", pos1.first, pos1.second);
            std::cout << error_message;
            // throw std::runtime_error(auto error_message);
        }

        auto returnNode = std::make_unique<ASTExpressionReturn>(std::move(returnValue));
        root->addChild(std::move(returnNode));

        // make sure that construction ends with ";"
        currentIter++;
        if (currentIter >= tokens.size()) {
            auto error_message = std::format("line {}:{}:Expected '{}' after return statement", pos.first, pos.second, lexer_.get()->delimitertIdentifier());
            std::cout << error_message;
            // throw std::runtime_error(error_message);
            break;
        }
        auto &[token2, pos2, value2] = tokens[currentIter];

        if (token2 != Lexer::Token::delimiter) {
            auto error_message = std::format("line {}:{}:Expected '{}' after return statement", pos2.first, pos2.second, lexer_.get()->delimitertIdentifier());
            std::cout << error_message;
            // throw std::runtime_error(auto error_message);
        }
        currentIter++; // consume ";"
        break;
    }

    case Lexer::Token::eof: {
      currentIter++;
      break;
    }
    
    default: {
        currentIter++;
        auto error_message = std::format("line {}:{}:Unexpected token while parsing", pos.first, pos.second);
        std::cout << error_message;
        // throw std::runtime_error(auto error_message);
    }
    }
  }

  return root;
}
