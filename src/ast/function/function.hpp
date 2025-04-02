#pragma once
#include "../base/base_node.hpp"
#include "../statement/statement.hpp"

#include <memory>
#include <deque>

class Function : public BaseNode {
 public:
  Function(
      std::string&& id, 
      std::unique_ptr<ParamList> param_list, 
      std::unique_ptr<CodeBlock> block
  )
    : id(id)
    , param_list(std::move(param_list))
    , block(std::move(block))
  {}

  DefineAccept();

  std::string id;
  std::unique_ptr<ParamList> param_list;
  std::unique_ptr<CodeBlock> block;
};