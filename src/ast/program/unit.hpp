#pragma once
#include "../base/base_node.hpp"
#include "../function/function.hpp"
#include <deque>
#include <memory>


class TranslUnit : public BaseNode {
 public:
  using Storage = std::deque<std::unique_ptr<Function>>;

  TranslUnit(Storage funcs)
    : funcs(std::move(funcs))
  {}

  DefineAccept();

  Storage funcs;
};