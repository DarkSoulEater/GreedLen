#pragma once

#include "visitor.hpp"
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>

#include <unordered_map>

#include "containers/SingleElemStack.hpp"

class LLVMIRVisitor : public Visitor {
 public:
  LLVMIRVisitor();

  void Run(TranslUnit* unit);

  // void Print();
  void Write(const std::string_view& file_name);

 private:
  #include "visitor.def"

  llvm::LLVMContext ctx_;
  llvm::Module module_;
  llvm::IRBuilder<> builder_;

  llvm::Function* cur_func_{nullptr};
  std::unordered_map<std::string_view, llvm::Value*> vars_;
  std::unordered_map<std::string_view, llvm::Function*> funcs_;

  std::vector<llvm::Type*> params_types_;
  std::vector<llvm::Value*> args_value_;
  std::vector<std::string_view> params_names_;

  SingleElemStack<llvm::Value*> value_stk_;
  SingleElemStack<std::string_view> bb_name_stk_;

  bool bb_finished_ret_{false};
};