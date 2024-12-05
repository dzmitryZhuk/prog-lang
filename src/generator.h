#pragma once

#include "ast.h"

#include <string>

using addr = uint32_t;

/*!
 * \brief Class that generates assembly code from AST
 */
class Generator
{
    public:
        explicit Generator(std::unique_ptr<ASTNode> ast);
        virtual ~Generator() = default;
        std::string generate();

    protected:
        virtual std::string generateHeader();
        virtual std::string generateFooter();

        virtual std::string generateSysCallExit(int exitCode);
        virtual std::string generateSysCallWrite(unsigned int fd, addr buf, addr count);
        virtual std::string generateSysCallRead(unsigned int fd, addr buf, addr count);
        virtual std::string generateSysCallReadStdin(addr buf, addr count);
        virtual std::string generateSysCallWriteStdout(addr buf, addr count);
        virtual std::string generateSysCallWriteStderr(addr buf, addr count);

        /*!
        * \brief Name of label that respond for entry point of current object file
        */
        std::string nameOfEntry_;
        /*!
        * \brief Name of label that respond for exit from program
        */
        std::string nameOfExit_;
        /*!
        * \brief AST according to which the assembler code will be generated
        */
        std::unique_ptr<ASTNode> ast_;
};
