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
  
  auto currentToken = [&]() -> const Lexer::TokenTuple& {
      if (currentIter >= tokens.size()) {
          throw std::runtime_error("Unexpected end of input while parsing");
      }
      return tokens[currentIter];
  };

  auto checkToken = [&](Lexer::Token expectedType) -> bool {
      return currentIter < tokens.size() && std::get<Lexer::Token>(currentToken()) == expectedType;
  };

  auto consumeToken = [&]() -> const Lexer::TokenTuple& {
      const auto& token = currentToken();
      ++currentIter;
      return token;
  };

  // start parsing
  std::unique_ptr<ASTNode> root = nullptr;

  while (currentIter < tokens.size()) {
      const auto& token = currentToken();

      switch (std::get<Lexer::Token>(token)) {
          case Lexer::Token::returning: {
              // parse "ret <smth>;"
              consumeToken(); // consume "ret"

              // next token is number or variable
              if (checkToken(Lexer::Token::number)) {
                  double value = std::get<double>(std::get<Lexer::TokenValue>(consumeToken()));
                  root = std::make_unique<ASTExpressionNumber>(value);
              } else if (checkToken(Lexer::Token::identifier)) {
                  std::string variableName = std::get<std::string>(std::get<Lexer::TokenValue>(consumeToken()));
                  root = std::make_unique<ASTExpressionVariable>(variableName);
              } else {  // TODO: add case if function call here
                auto pos = std::get<Lexer::TokenPos>(consumeToken());
                std::cout << std::format("line {}:{}:Expected a number or variable after 'ret'", pos.first, pos.second);
                  // throw std::runtime_error("Expected a number or variable after 'ret'");
              }

              // make sure that construction ends with ";"
              if (!checkToken(Lexer::Token::delimiter)) {
                auto pos = std::get<Lexer::TokenPos>(consumeToken());
                std::cout << std::format("line {}:{}:Expected '{}' after return statement", pos.first, pos.second, lexer_.get()->delimitertIdentifier());
                  // throw std::runtime_error(std::format("Expected '{}' after return statement", lexer_.get()->delimitertIdentifier()));
              }
              consumeToken(); // consume ";"
              break;
          }
          
          default: {
              // throw std::runtime_error("Unexpected token while parsing");
              auto pos = std::get<Lexer::TokenPos>(consumeToken());
              std::cout << std::format("line {}:{}:Unexpected token while parsing", pos.first, pos.second);
          }
      }
  }

  return root;
}
