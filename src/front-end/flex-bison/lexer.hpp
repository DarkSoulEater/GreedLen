#pragma once

#if ! defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#undef YY_DECL
#define YY_DECL yy::parser::symbol_type Lexer::ScanToken()

#include "flex-bison/parser.tab.hpp"

class Lexer : public yyFlexLexer {
 public:
  Lexer() {}
  virtual ~Lexer() {}
  virtual yy::parser::symbol_type ScanToken();
 private:
};