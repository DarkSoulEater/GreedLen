#pragma once

#include "flex-bison/lexer.hpp"
#include "flex-bison/parser.hpp"

class FrontEnd {
 public:
  FrontEnd();

  int ParseFile(std::ifstream* file);
 private:
  Lexer lexer_;
  friend yy::parser;
  yy::parser parser_;

  std::unique_ptr<TranslUnit> unit_;
};