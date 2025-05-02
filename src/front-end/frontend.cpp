#include "frontend.hpp"
#include <fstream>

#include "visitor/print.hpp"
#include "visitor/graphviz.hpp"
#include "visitor/interpreter.hpp"

FrontEnd::FrontEnd()
    : lexer_()
    , parser_(lexer_, *this)
{}

int FrontEnd::ParseFile(std::ifstream* file) {
    lexer_.yyrestart(file);

    auto res = parser_.parse();

    // PrintVisitor visitor;
    // unit_->Accept(&visitor);

    std::cerr << "OK\n";

    GraphvizVisitor vis;
    unit_->Accept(&vis);
    vis.Write("");

    InterpreterVisitor inerpreter;
    inerpreter.Interpret(unit_.get());

    return res;
}