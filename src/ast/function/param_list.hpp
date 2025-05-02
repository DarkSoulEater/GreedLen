#pragma once
#include "../base/base_node.hpp"
#include <memory>
#include <deque>

class ParamList : public BaseNode {
 public:
  using Storage = std::deque<std::unique_ptr<VarDecl>>;

  ParamList() {}

  ParamList(std::unique_ptr<VarDecl> var_decl) {
    Add(std::move(var_decl));
  }

  ParamList(Storage&& params)
    : params(std::move(params))
  {}

  void Add(std::unique_ptr<VarDecl> var_decl) {
    params.push_back(std::move(var_decl));
  }

  DefineAccept();

  Storage params;
};