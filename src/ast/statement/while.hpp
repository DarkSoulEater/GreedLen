#pragma once
#include "statement.hpp"
#include "../expression/expression.hpp"
#include "../code/code_block.hpp"

#include <memory>

class WhileStatement : public Statement {
 public:
  WhileStatement(
    std::unique_ptr<Expression> cond,
    std::unique_ptr<CodeBlock> block
  )
    : cond(std::move(cond))
    , block(std::move(block))
  {}

  DefineAccept();

  std::unique_ptr<Expression> cond;
  std::unique_ptr<CodeBlock> block;
};