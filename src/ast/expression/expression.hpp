#pragma once

#include "../base/base_node.hpp"

class Expression : public BaseNode {

};

class IntExpression : public Expression {
 public:
  IntExpression(int value)
    : value(value) {}

  DefineAccept();
  
  int value{0};
};