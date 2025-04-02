#pragma once
#include "function.hpp"

#include <memory>
#include <deque>

class FunctionList : public BaseNode {
 public:
  using Storage = std::deque<std::unique_ptr<Function>>;
  FunctionList(Storage&& funcs)
    : funcs(std::move(funcs))
  {}

  DefineAccept();

  Storage funcs;
};