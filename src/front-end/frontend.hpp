#pragma once

#include "argument/argument.hpp"
#include "flex-bison/lexer.hpp"
#include "flex-bison/parser.hpp"

class FrontEnd {
 public:
  FrontEnd(Argument& args);

  std::optional<std::unique_ptr<TranslUnit>>
  ParseFile(std::ifstream* file);
  
 private:
  Argument& args_;

  Lexer lexer_;
  friend yy::parser;
  yy::parser parser_;

  std::unique_ptr<TranslUnit> unit_;
};