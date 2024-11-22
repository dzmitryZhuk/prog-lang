#include "generator.h"
#include "utils.h"

#include <sstream>
#include <format>
#include <string_view>

using namespace utils;

constexpr ARCH cArch = ARCH::arm64;  
constexpr OS cOs = OS::mac;
constexpr std::string_view cIndent = "\t\t\t";

Generator::Generator()
  : nameOfEntry_("_start")
  , nameOfExit_("_exit")
{
}

std::string Generator::generate()
{
  std::stringstream asmString;
  asmString << generateHeader();
  asmString << std::format("{}:", nameOfEntry_) << std::endl;

  asmString << generateFooter();
  return asmString.str();
}

std::string Generator::generateHeader()
{
  std::stringstream asmString;
  switch (cOs)
  {
  case OS::mac:
  asmString << std::endl;
  asmString << std::format(".global {}", nameOfEntry_) << std::endl;
  asmString << ".align 4" << std::endl;
  asmString << std::endl;
    break;
  case OS::linux:
  case OS::win:
  default:
    break;
  }
  return asmString.str();
}

std::string Generator::generateFooter()
{
  std::stringstream asmString;
  switch (cOs)
  {
  case OS::mac:
  asmString << std::endl;
  asmString << std::format("{}:", nameOfExit_) << std::endl;
  asmString << std::format("{}mov X0, #0", cIndent) << std::endl;   // Use 0 return code
  asmString << std::format("{}mov X16, #1", cIndent) << std::endl;  // #1 sys call - exit
    asmString << std::format("{}svc	#0x80", cIndent) << std::endl;    // Call kernel
    asmString << std::endl;
    break;
  case OS::linux:
  case OS::win:
  default:
    break;
  }
  return asmString.str();
}
