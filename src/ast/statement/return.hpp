#pragma once
#include "statement.hpp"
#include "../expression/expression.hpp"
#include <memory>

class ReturnStatement : public Statement {
 public:
  ReturnStatement(std::unique_ptr<Expression> expr)
    : expr(std::move(expr))
  {}

  DefineAccept();

  std::unique_ptr<Expression> expr;
};