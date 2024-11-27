#pragma once

#define PROGRAM_NAME "compiller"
#define VERSION 0.1

////// lexer
// for cur line and cur line pos
// starting count from 1 or 0 like 1,2,3... or 0,1,2...
constexpr size_t cStartCountFrom = 1;
// identifier for definition of function
constexpr std::string_view cIdentFunc = "func";
// identifier for comment start
constexpr std::string_view cIdentComment = "#";
// identifier for definition of returning from program or function
constexpr std::string_view cIdentRet = "ret";
// identifier for assignment
constexpr std::string_view cIdentAssign = "=";
// identifier for splitting of operations
constexpr std::string_view cIdentDelim = ";";
//////