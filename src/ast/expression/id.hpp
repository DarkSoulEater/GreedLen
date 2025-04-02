#pragma once
#include "expression.hpp"
#include <string>

class IdExpression : public Expression {
 public:
  IdExpression(std::string&& id)
    : id(id)
  {}

  DefineAccept();

  std::string id;
};