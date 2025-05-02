#pragma once

#include "visitor/visitor.hpp"

#define DefiniteAccept(CLASS_NAME)            \
  void CLASS_NAME::Accept(Visitor* visitor) { \
    visitor->Visit(this);                     \
  }

#define DefineAccept()                      \
  void Accept(Visitor* visitor) override {  \
    visitor->Visit(this);                   \
  }

class BaseNode {
 public:
  virtual ~BaseNode() = default;
  virtual void Accept(Visitor* visitor) = 0;
};