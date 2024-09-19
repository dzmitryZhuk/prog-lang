#include "parser.h"

#include <fstream>

Parser::Parser(const std::filesystem::path &path)
    : file_(path)
{
  auto fileSize = std::filesystem::file_size(path);
  std::string fileContent;
  fileContent.reserve(fileSize);
  std::ifstream stream{path};
  stream.read(fileContent.data(), fileSize);
  stream.close();
  lexer_ = std::make_unique<Lexer>(fileContent);
}
