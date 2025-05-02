#pragma once
#include "expression.hpp"
#include "../function/param_value_list.hpp"
#include <string>

class CallFunction : public Expression {
 public:
  CallFunction(std::string&& id, std::unique_ptr<ParamValueList> param_value_list)
    : id(id)
    , param_value_list(std::move(param_value_list))
  {}

  DefineAccept();

  std::string id;
  std::unique_ptr<ParamValueList> param_value_list;
};