#include <iostream>
#include <filesystem>
#include "parser.h"

int main(int argc, char* argv[])
{
  std::cout << "compiller" << std::endl;

  std::filesystem::path path = argv[1];

  if(!std::filesystem::exists(path))
  {
    std::cerr << "File <" << path << "> don't exists!" << std::endl;
    return EXIT_FAILURE;
  }

  if (!std::filesystem::is_regular_file(path)) {
      std::cerr << "This path <" << path << "> is not a file!" << std::endl;
      return EXIT_FAILURE;
  }

  // Parser parser{path};
  // .
  // .
  // .

  return EXIT_SUCCESS;
}