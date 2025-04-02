#pragma once
#include "../base/base_node.hpp"
#include "../statement/statement.hpp"

#include <memory>
#include <deque>

class Function : public BaseNode {
 public:
  using Storage = std::deque<std::unique_ptr<Statement>>;

  Function(std::string&& id, std::unique_ptr<ParamList> param_list, Storage&& statements)
    : id(id)
    , param_list(std::move(param_list))
    , statements(std::move(statements))
  {}

  DefineAccept();

  std::string id;
  std::unique_ptr<ParamList> param_list;
  Storage statements;
};