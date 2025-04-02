#pragma once

#include "expression.hpp"
#include <memory>
#include <cassert>

class ArithmeticExpression : public Expression {
 public:
  enum class Type {
    ADD,
    SUB,
    MUL,
    DIV
  };

  ArithmeticExpression(
    Type type,
    std::unique_ptr<Expression> e1, 
    std::unique_ptr<Expression> e2
  )
    : type(type)
    , e1(std::move(e1))
    , e2(std::move(e2))
  {}

  const char* TypeToStr() const {
    switch (type) {
      case Type::ADD: return "+";
      case Type::SUB: return "-";
      case Type::MUL: return "*";
      case Type::DIV: return "/";
      default: {
        assert(0);
        return "";
      }
    }
  }

  DefineAccept();

  Type type;
  std::unique_ptr<Expression> e1;
  std::unique_ptr<Expression> e2;
};

// class AddExpression : public Expression {
//  public:
//   AddExpression(
//     std::unique_ptr<Expression> e1,
//     std::unique_ptr<Expression> e2
//   )
//     : e1(std::move(e1))
//     , e2(std::move(e2))
//   {}

//   DefineAccept();

//   std::unique_ptr<Expression> e1;
//   std::unique_ptr<Expression> e2;
// };

// class SubExpression : public Expression {
//   public:
//   SubExpression(
//     std::unique_ptr<Expression> e1,
//     std::unique_ptr<Expression> e2
//   )
//     : e1(std::move(e1))
//     , e2(std::move(e2))
//   {}
 
//   DefineAccept();

//   std::unique_ptr<Expression> e1;
//   std::unique_ptr<Expression> e2;
// };

// class MulExpression : public Expression {
//  public:
//   MulExpression(
//     std::unique_ptr<Expression> e1,
//     std::unique_ptr<Expression> e2
//   )
//     : e1(std::move(e1))
//     , e2(std::move(e2))
//   {}
 
//   DefineAccept();

//   std::unique_ptr<Expression> e1;
//   std::unique_ptr<Expression> e2;
// };

// class DivExpression : public Expression {
//  public:
//   DivExpression(
//     std::unique_ptr<Expression> e1,
//     std::unique_ptr<Expression> e2
//   )
//     : e1(std::move(e1))
//     , e2(std::move(e2))
//   {}
 
//   DefineAccept();
  
//   std::unique_ptr<Expression> e1;
//   std::unique_ptr<Expression> e2;
// };