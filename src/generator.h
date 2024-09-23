#pragma once

#include "ast.h"

#include <string>

/*!
 * \brief Class that generates assembly code from AST
 */
class Generator
{
    public:
        explicit Generator(/*AST tree*/);
        virtual ~Generator() = default;
        std::string generate();

    protected:
        virtual std::string generateHeader();
        virtual std::string generateFooter();

        /*!
        * \brief Name of label that respond for entry point of current object file
        */
        std::string nameOfEntry_;
        /*!
        * \brief Name of label that respond for exit from program
        */
        std::string nameOfExit_;
};
