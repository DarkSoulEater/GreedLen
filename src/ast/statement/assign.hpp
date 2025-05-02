#pragma once
#include "statement.hpp"
#include "../expression/expression.hpp"
#include <string>
#include <memory>

class AssignStatement : public Statement {
 public:
  AssignStatement(std::string&& id, std::unique_ptr<Expression> expr)
    : id(id)
    , expr(std::move(expr))
  {}

  DefineAccept();

  std::string id;
  std::unique_ptr<Expression> expr;
};