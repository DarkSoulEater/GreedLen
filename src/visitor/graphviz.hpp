#pragma once

#include "visitor.hpp"

#include <string_view>
#include <util/dot.hpp>
#include <cassert>

class BaseNode;

class GraphvizVisitor : public Visitor {
 public:
  GraphvizVisitor() {}

  #define DefAstNode(CLASS_NAME) \
  void Visit(CLASS_NAME*) override;
  #include "ast/ast.def"

  bool Write(const std::string_view& out_file_name);

 private:
  Dot graph_;

  class SingleElemStack {
   public:
    using Value = Dot::Vertex;

    void Push(Value value) {
      assert(!value_.has_value());
      value_ = value;
    }

    Value Pop() {
      assert(value_.has_value());
      Value value = value_.value_or(0);
      value_.reset();
      return value;
    }
   private:
    std::optional<Value> value_{std::nullopt};
  } stack_vertex_;
};