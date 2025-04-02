#pragma once

#include "visitor.hpp"
#include <unordered_map>
#include <string_view>
#include <vector>
#include <cassert>
#include <ranges>
#include <stack>

class InterpreterVisitor : public Visitor {
 public:
  InterpreterVisitor() {}

  void Interpret(TranslUnit* unit);

  #include "visitor.def"

 private:
  std::string_view main_func_name = "main";

  std::unordered_map<std::string_view, Function*> funcs_;

  // Draft Scope
  class Scope {
   public:
    void Push() {
      scopes_.push_back({});
    }

    void Pop() {
      assert(!scopes_.empty());
      scopes_.pop_back();
    }

    void Add(std::string_view var_name, int value) {
      scopes_.back()[var_name] = value;
    }

    int Get(std::string_view var_name) {
      for (auto& vars_ : scopes_ | std::views::reverse) {
        auto var = vars_.find(var_name);
        if (var != vars_.end()) {
          return var->second;
        }
      }

      // TODO: If not found
      assert(0);
      return 0;
    }

    auto Size() {
      return scopes_.size();
    }

    void SetRetValue(int value) { ret_val_ = value; }
    int GetRetValue() { return ret_val_; }

    bool GetReturn() {
      if (call_return_) {
        call_return_ = false;
        return true;
      }
      return false;
    }

    void Return() { call_return_ = true; }

   private:
    std::vector<std::unordered_map<std::string_view, int>> scopes_;
    int ret_val_;
    bool call_return_{false};
  };

  std::vector<Scope> scopes_;

  Scope& CurrScope() {
    return scopes_.back();
  }

  void PushScope() {
    scopes_.push_back({});
    CurrScope().Push();
  }

  void PopScope() {
    assert(!scopes_.empty());
    auto ret_val = CurrScope().GetRetValue();
    scopes_.pop_back();
    if (!scopes_.empty()) {
      CurrScope().SetRetValue(ret_val);
    }
  }

  std::vector<std::string_view> params_name_;
  std::vector<int> params_value_;
};