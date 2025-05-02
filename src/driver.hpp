#pragma once
#include "front-end/frontend.hpp"

class Driver {
 public:
  Driver();

  void ParseArgs(int argc, const char* argv[]);

 private:
  FrontEnd front_end_;

  int ParseFile(const std::string_view& file_name);
};