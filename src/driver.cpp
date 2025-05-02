#include "driver.hpp"

#include <fstream>

#include "visitor/print.hpp"
#include "visitor/graphviz.hpp"
#include "visitor/interpreter.hpp"
#include "visitor/llvmir.hpp"

Driver::Driver()
    : front_end_(args_)
{}

void Driver::ParseArgs(int argc, const char* argv[]) {
    llvm::cl::ParseCommandLineOptions(argc, argv, "GL Compiler\n");

    ParseFile(args_.InputFilename);
}

int Driver::ParseFile(const std::string_view& file_name) {
    std::ifstream stream;
    stream.open(file_name.data());

    if (!stream.is_open()) {
        assert(0);
        abort();
    }

    auto unit = front_end_.ParseFile(&stream);
    
    stream.close();

    if (!unit.has_value())
        return 1;
    
    if (args_.Dot.getNumOccurrences() > 0) {
        GraphvizVisitor vis;
        vis.Visit(static_cast<BaseNode*>(unit->get()));

        if (!args_.Dot.empty()) {
            vis.Write(args_.Dot);
        } else {
            assert(0 && "Not impl. Use --dot=filename"); // TODO: implement
        }
    }

    if (args_.Interpret) {
        InterpreterVisitor visitor;
        visitor.Interpret(unit->get());
    }

    if (!args_.GenerateLLMIR.empty()) {
        LLVMIRVisitor visitor;
        visitor.Run(unit->get());
        visitor.Write(args_.GenerateLLMIR);
    }

    return 0;
}