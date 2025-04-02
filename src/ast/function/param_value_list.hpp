#pragma once
#include "../expression/expression.hpp"
#include <memory>
#include <deque>

class ParamValueList : public BaseNode {
 public:
  using Storage = std::deque<std::unique_ptr<Expression>>;
  ParamValueList() {}

  ParamValueList(std::unique_ptr<Expression> expr) {
    Add(std::move(expr));
  }

  ParamValueList(Storage&& params_value)
    : params_value(std::move(params_value))
  {}

  void Add(std::unique_ptr<Expression> expr) {
    params_value.push_back(std::move(expr));
  }

  DefineAccept();

  Storage params_value;
};