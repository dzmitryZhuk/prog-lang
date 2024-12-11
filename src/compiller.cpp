#include <iostream>
#include <filesystem>
#include "constants.h"
#include "parser.h"
#include "generator.h"
#include "log.h"

constexpr std::string_view help_message = "Usage: " PROGRAM_NAME " [options]\n\n" \
                                          "Options:\n"
                                          "  -h, --help         Show this help message and exit\n"
                                          ;

int main(int argc, char* argv[])
{
  LOG_INFO(std::format("{} v{}", PROGRAM_NAME, VERSION));
  std::system("pwd");
  if (argc > 1)
  {
    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
    {
      std::cout << help_message;
      return 0;
    }
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

#ifdef __APPLE__
    auto abs_out_asm = std::filesystem::absolute(output_path);
    auto abs_out_o = abs_out_asm.parent_path().append("out.o");
    auto abs_out = abs_out_o.parent_path().append("out");
    std::system(std::format("as {} -o {}", abs_out_asm.string(), abs_out_o.string()).c_str());
    std::system(std::format("ld {} -o {} -lSystem -syslibroot `xcrun -sdk macosx --show-sdk-path` -e _start -arch arm64", abs_out_o.string(), abs_out.string()).c_str());
#endif
  }
  else
  {

  }

  return EXIT_SUCCESS;
}