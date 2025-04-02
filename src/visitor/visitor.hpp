#pragma once
#include "ast/fwd.hpp"

class Visitor {
 public:

  #define DefAstNode(CLASS_NAME) \
  virtual void Visit(CLASS_NAME*) = 0;
  #include "ast/ast.def"

};