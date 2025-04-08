#include "llvmir.hpp"
#include "ast/ast.hpp"
#include <llvm/IR/Verifier.h>
#include <llvm/IR/BasicBlock.h>

#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/FileSystem.h>

LLVMIRVisitor::LLVMIRVisitor()
  : module_("test", ctx_)
  , builder_(ctx_)
{}

void LLVMIRVisitor::Run(TranslUnit* unit) {
  unit->Accept(this);
}

// void LLVMIRVisitor::Print() {
//   module_.print(llvm::outs(), nullptr);
// }

void LLVMIRVisitor::Write(const std::string_view& file_name) {
  std::error_code code;
  llvm::raw_fd_ostream out(file_name, code, llvm::sys::fs::OF_None);

  if (code) {
    assert(0); // TODO:
  }

  module_.print(out, nullptr);
  out.close();
}

void LLVMIRVisitor::Visit(TranslUnit* unit) {
  for (auto& func : unit->funcs) {
    func->Accept(this);
  }
}

void LLVMIRVisitor::Visit(Function* func) {
  vars_.clear();
  params_names_.clear();

  func->param_list->Accept(this);
  
  auto* func_type = llvm::FunctionType::get(
    builder_.getInt32Ty(),
    std::move(params_types_),
    false
  );
  params_types_ = {};

  auto* llvm_func = llvm::Function::Create(
    func_type,
    llvm::Function::ExternalLinkage,
    func->id,
    module_
  );

  funcs_[func->id] = llvm_func;
  cur_func_ = llvm_func;

  auto* prepare_arg_bb 
    = llvm::BasicBlock::Create(ctx_, "prepare_arg", cur_func_);
  builder_.SetInsertPoint(prepare_arg_bb);

  size_t ind = 0;
  for (auto arg_it = llvm_func->arg_begin(); ind != params_names_.size(); ++arg_it, ++ind) {
    arg_it->setName(params_names_[ind]);
    auto* val = llvm_func->getArg(ind);
    // auto value = builder_.CreateAlloca(builder_.getInt32Ty(), nullptr, params_names_[ind]);
    auto value = builder_.CreateAlloca(builder_.getInt32Ty(), nullptr);
    builder_.CreateStore(val, value);
    vars_[params_names_[ind]] = value;
  }

  bb_name_stk_.Push("entry");
  func->block->Accept(this);

  llvm::BasicBlock* entry_bb = nullptr;
  for (auto& BB : *llvm_func) {
    if (BB.getName() == "entry") {
      entry_bb = &BB;
    }
  }
  assert(entry_bb);

  builder_.SetInsertPoint(prepare_arg_bb);
  builder_.CreateBr(entry_bb);

  llvm::verifyFunction(*llvm_func);
}

void LLVMIRVisitor::Visit(ParamList* params) {
  for (auto& param : params->params) {
    params_types_.push_back(builder_.getInt32Ty());
    params_names_.push_back(param->id);
  }
}

void LLVMIRVisitor::Visit(CodeBlock* block) {
  auto* bb = llvm::BasicBlock::Create(ctx_, bb_name_stk_.Pop(), cur_func_);
  builder_.SetInsertPoint(bb);

  for (auto& st : block->statements) {
    st->Accept(this);
  }
}

void LLVMIRVisitor::Visit(AssignStatement* st) {
  auto* var = vars_[st->id];

  st->expr->Accept(this);

  builder_.CreateStore(value_stk_.Pop(), var);
}

void LLVMIRVisitor::Visit(IfStatement* st) {
  auto if_cond_bb =
    llvm::BasicBlock::Create(ctx_, "if.cond", cur_func_);

  builder_.CreateBr(if_cond_bb);

  // Body BB
  bb_name_stk_.Push("if.body");
  st->block->Accept(this);
  auto if_body_bb = builder_.GetInsertBlock();

  auto if_merge_bb =
    llvm::BasicBlock::Create(ctx_, "if.merge", cur_func_);

  if (!bb_finished_ret_) {
    builder_.CreateBr(if_merge_bb);
  }
  bb_finished_ret_ = false;

  // Condition BB
  builder_.SetInsertPoint(if_cond_bb);
  st->cond->Accept(this);
  auto* lhs = value_stk_.Pop();
  auto* rhs = builder_.getInt32(0);
  auto* cond_val = builder_.CreateICmpNE(lhs, rhs);

  builder_.CreateCondBr(cond_val, if_body_bb, if_merge_bb);

  // Merge BB
  builder_.SetInsertPoint(if_merge_bb);
}

void LLVMIRVisitor::Visit(WhileStatement* st) {
  auto* while_cond_bb 
    = llvm::BasicBlock::Create(ctx_, "while.cond", cur_func_);
  
  builder_.CreateBr(while_cond_bb);
  
  // auto insert_point = builder_.GetInsertPoint();
  bb_name_stk_.Push("while.body");
  st->block->Accept(this);
  builder_.CreateBr(while_cond_bb);
  
  auto* while_body_bb = builder_.GetInsertBlock();
  builder_.SetInsertPoint(while_cond_bb);
  st->cond->Accept(this);

  auto* lhs = value_stk_.Pop();
  auto* rhs = builder_.getInt32(0);
  auto* cond_val = builder_.CreateICmpNE(lhs, rhs);

  auto* while_next_bb = llvm::BasicBlock::Create(ctx_, "while.next", cur_func_);
  builder_.CreateCondBr(cond_val, while_body_bb, while_next_bb);
  
  builder_.SetInsertPoint(while_next_bb);
}

void LLVMIRVisitor::Visit(PrintStatement* st) {
  // assert(0);
}

void LLVMIRVisitor::Visit(ReturnStatement* st) {
  st->expr->Accept(this);
  builder_.CreateRet(value_stk_.Pop());
  bb_finished_ret_ = true;
}

void LLVMIRVisitor::Visit(VarDecl* var) {
  // auto* val = builder_.CreateAlloca(builder_.getInt32Ty(), nullptr, var->id);
  auto* val = builder_.CreateAlloca(builder_.getInt32Ty(), nullptr);
  vars_[var->id] = val;
}

void LLVMIRVisitor::Visit(CallFunction* call) {
  call->param_value_list->Accept(this);
  auto res = builder_.CreateCall(funcs_[call->id], std::move(args_value_));
  args_value_ = {};

  value_stk_.Push(res);
}

void LLVMIRVisitor::Visit(ParamValueList* params) {
  for (auto& arg : params->params_value) {
    arg->Accept(this);
    args_value_.push_back(value_stk_.Pop());
  }
}

void LLVMIRVisitor::Visit(IntExpression* expr) {
  auto* val = builder_.getInt32(expr->value);
  value_stk_.Push(val);
}

void LLVMIRVisitor::Visit(ArithmeticExpression* expr) {
  expr->e1->Accept(this);
  auto* lhs = value_stk_.Pop();

  expr->e2->Accept(this);
  auto* rhs = value_stk_.Pop();

  llvm::Value* res = nullptr;
  switch (expr->type) {
    case ArithmeticExpression::Type::ADD: {
      res = builder_.CreateAdd(lhs, rhs);
    } break;

    case ArithmeticExpression::Type::SUB: {
      res = builder_.CreateSub(lhs, rhs);
    } break;

    case ArithmeticExpression::Type::MUL: {
      res = builder_.CreateMul(lhs, rhs);
    } break;

    case ArithmeticExpression::Type::DIV: {
      res = builder_.CreateSDiv(lhs, rhs);
    } break;

    default: {
      assert(0);
    };
  }

  value_stk_.Push(res);
}

void LLVMIRVisitor::Visit(IdExpression* expr) {
  auto* var = vars_[expr->id];
  auto* val = builder_.CreateLoad(builder_.getInt32Ty(), var);

  value_stk_.Push(val);
}