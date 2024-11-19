#include "parser.h"

#include <fstream>

Parser::Parser(const std::filesystem::path &path)
    : file_(path)
{
  std::ifstream stream{path};
  std::string fileContent((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
  stream.close();
  lexer_ = std::make_unique<Lexer>(fileContent);
}
