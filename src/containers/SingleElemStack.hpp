#pragma once

#include <optional>

template <typename T>
class SingleElemStack {
  public:
   using Value = T;

   void Push(Value value) {
     assert(!value_.has_value());
     value_ = value;
   }

   Value Pop() {
     assert(value_.has_value());
     Value value = value_.value();
     value_.reset();
     return value;
   }
  private:
   std::optional<Value> value_{std::nullopt};
};