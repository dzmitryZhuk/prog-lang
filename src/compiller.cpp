#include <iostream>
#include <filesystem>
#include <fstream>
#include "parser.h"
#include "generator.h"

int main(int argc, char* argv[])
{
  std::cout << "compiller" << std::endl;

  std::filesystem::path input_path = argv[1];

  if(!std::filesystem::exists(input_path))
  {
    std::cerr << "File <" << input_path << "> don't exists!" << std::endl;
    return EXIT_FAILURE;
  }

  if (!std::filesystem::is_regular_file(input_path)) {
      std::cerr << "This path <" << input_path << "> is not a file!" << std::endl;
      return EXIT_FAILURE;
  }
  
  Parser parser{input_path};
  auto ast = parser.parse();
  Generator gen(std::move(ast));
  auto generated_str = gen.generate();
  
  std::filesystem::path output_path = input_path.parent_path().append("out.asm");
  std::fstream f(output_path, std::ios::out);
  f << generated_str;
  f.close();

  return EXIT_SUCCESS;
}