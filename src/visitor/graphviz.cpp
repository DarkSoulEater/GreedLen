#include "graphviz.hpp"
#include "ast/ast.hpp"

void GraphvizVisitor::Visit(IntExpression* expr) {
  auto vert = graph_.AddVertexWithCopy(std::to_string(expr->value));
  stack_vertex_.Push(vert);
}

void GraphvizVisitor::Visit(ArithmeticExpression* expr) {
  auto vert = graph_.AddVertex(expr->TypeToStr());

  expr->e1->Accept(this);
  graph_.AddEdge(vert, stack_vertex_.Pop(), "");

  expr->e2->Accept(this);
  graph_.AddEdge(vert, stack_vertex_.Pop(), "");

  stack_vertex_.Push(vert);
}

void GraphvizVisitor::Visit(IdExpression* expr) {
  auto vert = graph_.AddVertex(expr->id);
  stack_vertex_.Push(vert);
}

void GraphvizVisitor::Visit(CallFunction* call) {
  auto vert = graph_.AddVertex("Call");
  
  auto vert_id = graph_.AddVertex(call->id);
  graph_.AddEdge(vert, vert_id, "");

  call->param_value_list->Accept(this);
  graph_.AddEdge(vert, stack_vertex_.Pop(), "");

  stack_vertex_.Push(vert);
}

void GraphvizVisitor::Visit(FunctionList* funcs) {
  assert(0);
}

void GraphvizVisitor::Visit(Function* func) {
  auto vert = graph_.AddVertex(func->id);

  for (auto& st : func->statements) {
    st->Accept(this);
    graph_.AddEdge(vert, stack_vertex_.Pop(), "");
  }

  stack_vertex_.Push(vert);
}

void GraphvizVisitor::Visit(ParamList* params) {
  auto vert = graph_.AddVertex("Parametrs");

  for (auto& param : params->params) {
    param->Accept(this);
    graph_.AddEdge(vert, stack_vertex_.Pop(), "");
  }

  stack_vertex_.Push(vert);
}

void GraphvizVisitor::Visit(ParamValueList* params_val) {
  auto vert = graph_.AddVertex("Parametrs");

  for (auto& param : params_val->params_value) {
    param->Accept(this);
    graph_.AddEdge(vert, stack_vertex_.Pop(), "");
  }

  stack_vertex_.Push(vert);
}

void GraphvizVisitor::Visit(TranslUnit* unit) {
  auto vert = graph_.AddVertex("Unit");

  for (const auto& func : unit->funcs) {
    auto func_vert = graph_.AddVertex(func->id);
    graph_.AddEdge(vert, func_vert, "");

    func->param_list->Accept(this);
    graph_.AddEdge(func_vert, stack_vertex_.Pop(), "");

    func->Accept(this);
    stack_vertex_.Pop(); // Consume vertex
  }

  stack_vertex_.Push(vert);
}

void GraphvizVisitor::Visit(Statement* st) {
  auto vert = graph_.AddVertex("St");
  stack_vertex_.Push(vert);
}

void GraphvizVisitor::Visit(AssignStatement* st) {
  auto vert = graph_.AddVertex("=");

  auto vert_id = graph_.AddVertex(st->id);
  graph_.AddEdge(vert, vert_id, "");

  st->expr->Accept(this);
  graph_.AddEdge(vert, stack_vertex_.Pop(), "");

  stack_vertex_.Push(vert);
}

void GraphvizVisitor::Visit(VarDecl* var) {
  auto vert = graph_.AddVertex(var->id);
  stack_vertex_.Push(vert);
}

void GraphvizVisitor::Visit(ReturnStatement* st) {
  auto vert = graph_.AddVertex("return");
  
  st->expr->Accept(this);
  graph_.AddEdge(vert, stack_vertex_.Pop(), "");

  stack_vertex_.Push(vert);
}

bool GraphvizVisitor::Write(const std::string_view& out_file_name) {
  return graph_.Write("doc/graph.dot");
  return graph_.Write(out_file_name);
}