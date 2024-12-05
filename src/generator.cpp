#include "generator.h"
#include "utils.h"

#include <sstream>
#include <format>
#include <string_view>

using namespace utils;

constexpr ARCH cArch = ARCH::arm64;  
constexpr OS cOs = OS::mac;
constexpr std::string_view cIndent = "\t\t\t";

Generator::Generator(std::unique_ptr<ASTNode> ast)
  : nameOfEntry_("_start")
  , nameOfExit_("_instant_success_exit")
  , ast_(std::move(ast))
{
}

std::string Generator::generate()
{
  std::stringstream asmString;
  asmString << generateHeader();
  asmString << std::format("{}:", nameOfEntry_) << std::endl;

  // generate main code
  for (const auto &node : ast_->children()) {
    if (node.get()->type().has_value()) {
      switch (node.get()->type().value())
      {
      case Lexer::Token::returning:
      {
        const auto &return_value = dynamic_cast<ASTExpressionReturn*>(node.get())->value();
        if (return_value->type().has_value())
        {
          switch (return_value->type().value())
          {
          case Lexer::Token::number:
          {
            auto node = dynamic_cast<const ASTExpressionNumber*>(return_value);
            const auto number = node->value();
            const auto numer_as_int = static_cast<const int>(number);
            asmString << generateSysCallExit(numer_as_int);
            break;
          }
          default:
            break;
          }
        }
        break;
      }
      default:
        break;
      }
    }
  }

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
  asmString << std::endl;
  asmString << std::format("{}:", nameOfExit_) << std::endl;
  asmString << generateSysCallExit(0);
  asmString << std::endl;
  return asmString.str();
}

std::string Generator::generateSysCallExit(int exitCode)
{
  std::stringstream asmString;
  int syscall_number = 1; // arm (32-bit/EABI)
  switch (cOs)
  {
  case OS::mac:
    asmString << std::format("{}mov X0, #{}", cIndent, exitCode) << std::endl;
    asmString << std::format("{}mov X16, #{}", cIndent, syscall_number) << std::endl;
    asmString << std::format("{}svc	#0x80", cIndent) << std::endl;
    break;
  case OS::linux:
  case OS::win:
  default:
    break;
  }
  return asmString.str();
}

std::string Generator::generateSysCallWrite(unsigned int fd, addr buf, addr count)
{
  std::stringstream asmString;
  int syscall_number = 4; // arm (32-bit/EABI)
  switch (cOs)
  {
  case OS::mac:
  asmString << std::format("{}mov X0, #{}", cIndent, fd) << std::endl;
  asmString << std::format("{}mov X1, {}", cIndent, buf) << std::endl;
  asmString << std::format("{}mov X2, {}", cIndent, count) << std::endl;
  asmString << std::format("{}mov X16, #{}", cIndent, syscall_number) << std::endl;
  asmString << std::format("{}svc	#0x80", cIndent) << std::endl;
    break;
  case OS::linux:
  case OS::win:
  default:
    break;
  }
  return asmString.str();
}

std::string Generator::generateSysCallRead(unsigned int fd, addr buf, addr count)
{
  std::stringstream asmString;
  int syscall_number = 3; // arm (32-bit/EABI)
  switch (cOs)
  {
  case OS::mac:
  asmString << std::format("{}mov X0, #{}", cIndent, fd) << std::endl;
  asmString << std::format("{}mov X1, {}", cIndent, buf) << std::endl;
  asmString << std::format("{}mov X2, {}", cIndent, count) << std::endl;
  asmString << std::format("{}mov X16, #{}", cIndent, syscall_number) << std::endl;
  asmString << std::format("{}svc	#0x80", cIndent) << std::endl;
    break;
  case OS::linux:
  case OS::win:
  default:
    break;
  }
  return asmString.str();
}

std::string Generator::generateSysCallReadStdin(addr buf, addr count)
{
    return generateSysCallRead(0, buf, count);
}

std::string Generator::generateSysCallWriteStdout(addr buf, addr count)
{
  return generateSysCallWrite(1, buf, count);
}

std::string Generator::generateSysCallWriteStderr(addr buf, addr count)
{
  return generateSysCallWrite(2, buf, count);
}
