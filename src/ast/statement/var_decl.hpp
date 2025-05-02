#pragma once
#include "statement.hpp"
#include <string>

class VarDecl : public Statement {
 public:
  VarDecl(std::string&& id)
    : id(id)
  {}

  DefineAccept();

  std::string id;
};