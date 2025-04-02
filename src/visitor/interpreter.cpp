#include "interpreter.hpp"
#include <cassert>
#include "ast/ast.hpp"
#include <ranges>
#include <iostream>

void InterpreterVisitor::Interpret(TranslUnit* unit) {
  PushScope();

  unit->Accept(this);
  std::cout << "Main returned with code: " << CurrScope().GetRetValue() << "\n\n";

  PopScope();
}

void InterpreterVisitor::Visit(TranslUnit* unit) {
  for (auto& func: unit->funcs) {
    funcs_[func->id] = func.get();
  }

  PushScope();
  funcs_[main_func_name]->Accept(this);
  PopScope();
}

void InterpreterVisitor::Visit(Function* func) {
  std::cerr << "Call: " << func->id << "\n";

  func->block->Accept(this);

  std::cerr << "End: " << func->id << ". Ret = " << CurrScope().GetRetValue() << "\n";
}

void InterpreterVisitor::Visit(CodeBlock* block) {
  // CurrScope().Push();

  for (auto& st : block->statements) {
    st->Accept(this);

    if (CurrScope().GetReturn()) {
      CurrScope().Return();
      break;
    }
  }

  // CurrScope().Pop();
}

void InterpreterVisitor::Visit(AssignStatement* st) {
  std::cout << "->ST: =\n";
  st->expr->Accept(this);
  // std::cout << CurrScope().GetReturn();
  // std::cout << "ST: =\n";
  CurrScope().Add(st->id, CurrScope().GetRetValue());
  std::cout << "<-ST: =\n";
}

void InterpreterVisitor::Visit(IfStatement* st) {
  st->cond->Accept(this);
  auto cond = CurrScope().GetRetValue();
  if (cond) {
    st->block->Accept(this);
  }
}

void InterpreterVisitor::Visit(WhileStatement* st) {
  st->cond->Accept(this);
  auto cond = CurrScope().GetRetValue();

  while (cond) {
    st->block->Accept(this);

    st->cond->Accept(this);
    cond = CurrScope().GetRetValue();
  }
}

void InterpreterVisitor::Visit(PrintStatement* st) {
  st->expr->Accept(this);
  std::cout << "Print: " << CurrScope().GetRetValue() << "\n";
}

void InterpreterVisitor::Visit(ReturnStatement* st) {
  st->expr->Accept(this);
  CurrScope().Return();
}

void InterpreterVisitor::Visit(VarDecl* var) {
  return; // NOTHING NOW
}

void InterpreterVisitor::Visit(CallFunction* call) {
  std::cout << "->Call:\n";
  call->param_value_list->Accept(this);

  auto func_it = funcs_.find(call->id);
  if (func_it == funcs_.end()) {
    // TODO:
    assert(0);
  }
  
  PushScope();
  auto func = func_it->second;
  func->param_list->Accept(this);
  if (params_name_.size() != params_value_.size()) {
    assert(0); // TODO:
  }

  std::cout << func->id << "(";
  for (auto& param : params_name_ | std::views::reverse) {
    auto name = param;
    auto value = params_value_.back();
    params_value_.pop_back();

    CurrScope().Add(name, value);

    std::cout << value << ", ";
  }
  params_name_.clear();
  std::cout << ")\n";

  func->Accept(this);
  CurrScope().GetRetValue(); // Consume
  PopScope();
  std::cout << "<-Call:\n";
}

void InterpreterVisitor::Visit(ParamList* params) {
  assert(params_name_.empty());
  for (auto& param : params->params) {
    params_name_.push_back(param->id);
  }
}

void InterpreterVisitor::Visit(ParamValueList* params_val) {
  assert(params_value_.empty());
  for (auto& param : params_val->params_value) {
    param->Accept(this);
    params_value_.push_back(CurrScope().GetRetValue());
  }
}

void InterpreterVisitor::Visit(IntExpression* expr) {
  CurrScope().SetRetValue(expr->value);
}

void InterpreterVisitor::Visit(ArithmeticExpression* expr) {
  std::cout << "->E:\n";
  expr->e1->Accept(this);
  auto val1 = CurrScope().GetRetValue();

  expr->e2->Accept(this);
  auto val2 = CurrScope().GetRetValue();

  std::cout << "Val1 = " << val1 << " Val2 = " << val2 << "\n";
  
  switch (expr->type) {
    case ArithmeticExpression::Type::ADD: {
      CurrScope().SetRetValue(val1 + val2);
    } break;;
    
    case ArithmeticExpression::Type::SUB: {
      CurrScope().SetRetValue(val1 - val2);
    } break;

    case ArithmeticExpression::Type::MUL: {
      CurrScope().SetRetValue(val1 * val2);
    } break;

    case ArithmeticExpression::Type::DIV: {
      CurrScope().SetRetValue(val1 / val2);
    } break;
  }

  std::cout << "<-E: Ret = " << CurrScope().GetRetValue() << "\n";
}

void InterpreterVisitor::Visit(IdExpression* expr) {
  CurrScope().SetRetValue(CurrScope().Get(expr->id));
}