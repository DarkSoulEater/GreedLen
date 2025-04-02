#pragma once
#include "../base/base_node.hpp"
#include "../statement/statement.hpp"
#include <memory>
#include <deque>

class CodeBlock : public BaseNode {
 public:
  using Storage = std::deque<std::unique_ptr<Statement>>;

  CodeBlock(Storage&& statements)
    : statements(std::move(statements))
  {}

  DefineAccept();

  Storage statements;
};