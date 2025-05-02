#pragma once

#include <llvm/Support/CommandLine.h>

struct Argument {
  // llvm::cl::opt<bool> StopAfterAsmOrIR{
  //     "S",
  //     llvm::cl::desc("Only run preprocess and compilation steps")
  //   };
    
  llvm::cl::opt<std::string> GenerateLLMIR{
    "S",
    llvm::cl::desc("Generate LLVM IR"),
    llvm::cl::value_desc("filename")
  };

  llvm::cl::opt<bool> Interpret{
    "interpret",
    llvm::cl::desc("Start interpreter after compile")
  };

  llvm::cl::opt<std::string> Dot{
    "dot",
    llvm::cl::desc("Create dot dump file"),
    llvm::cl::value_desc("filename"),
    llvm::cl::ValueOptional,
    llvm::cl::init("")
  };

  llvm::cl::opt<std::string> InputFilename{
    llvm::cl::desc("file"),
    llvm::cl::Positional,
    llvm::cl::Required
  };
};